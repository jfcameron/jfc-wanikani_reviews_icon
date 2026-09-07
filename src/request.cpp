// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/config.h>
#include <jfc/wanikani_reviews_icon/request.h>

#include <jfc/http/curl_context.h>
#include <jfc/http/request.h>
#include <jfc/http/types.h>

#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using namespace jfc;
using namespace jfc::wanikani_reviews_icon;

namespace {
    constexpr const char *SUMMARY_URL = "https://api.wanikani.com/v2/summary";
    constexpr const char *API_REVISION = "Wanikani-Revision: 20170710";

    constexpr jfc::http::milliseconds_type TIMEOUT_MILLISECONDS = 20000;

    class _worker final {
    public:
        void submit(std::vector<jfc::http::task_type> &&aTasks) {
            {
                const std::lock_guard<std::mutex> lock(m_Mutex);

                for (auto &task : aTasks) m_Tasks.push_back(std::move(task));
            }

            m_Ready.notify_one();
        }

        _worker()
        : m_Thread([this]() {
            for (;;) {
                jfc::http::task_type task;

                {
                    std::unique_lock<std::mutex> lock(m_Mutex);

                    m_Ready.wait(lock, [this]() { return m_bStopping || !m_Tasks.empty(); });

                    if (m_bStopping && m_Tasks.empty()) return;

                    task = std::move(m_Tasks.front());
                    m_Tasks.pop_front();
                }

                task();
            }
        }) {}

        ~_worker() {
            {
                const std::lock_guard<std::mutex> lock(m_Mutex);

                m_bStopping = true;
            }

            m_Ready.notify_all();

            if (m_Thread.joinable()) m_Thread.join();
        }

    private:
        std::mutex m_Mutex;
        std::condition_variable m_Ready;
        std::deque<jfc::http::task_type> m_Tasks;
        bool m_bStopping = false;

        std::thread m_Thread;
    };

    struct _session final {
        _worker worker;

        jfc::http::context_shared_ptr_type pContext;

        std::size_t outstanding = 0;

        _session()
        : pContext(jfc::http::curl_context::make({
            .submit = [this](std::vector<jfc::http::task_type> &&aTasks) {
                worker.submit(std::move(aTasks));
            }
        })) {}
    };

    [[nodiscard]] jfc::wanikani_reviews_icon::request::failure to_failure(const jfc::http::error aError) {
        using failure = jfc::wanikani_reviews_icon::request::failure;

        switch (aError) {
            case jfc::http::error::network_error:
            case jfc::http::error::unsupported_protocol:
                return failure::network;

            case jfc::http::error::http_error:
                return failure::rejected;

            default:
                return failure::other;
        }
    }

    std::unique_ptr<_session> g_pSession;

    [[nodiscard]] _session &_session_instance() {
        if (!g_pSession) g_pSession = std::make_unique<_session>();

        return *g_pSession;
    }
}

void jfc::wanikani_reviews_icon::request::submit_summary(
    jfc::wanikani_reviews_icon::request::response_handler_type aSucceededHandler,
    jfc::wanikani_reviews_icon::request::failed_handler_type aFailedHandler
) {
    auto &session = _session_instance();

    if (session.outstanding) return;

    const jfc::http::request_config config{
        .user_agent = "wanikani_reviews_icon",
        .timeout_milliseconds = TIMEOUT_MILLISECONDS,
        .headers = {
            API_REVISION,
            std::string("Authorization: Bearer ") + config::get_wanikani_token()
        }
    };

    const auto pGet = session.pContext->make_get(SUMMARY_URL, config,
        [aSucceededHandler](jfc::http::response_data_type aData) {
            aSucceededHandler(response_data_type(aData.begin(), aData.end()));
        },
        [aFailedHandler](const jfc::http::error aError) {
            aFailedHandler(to_failure(aError));
        });

    if (!pGet || !pGet->try_submit()) {
        aFailedHandler(request::failure::other);
        return;
    }

    ++session.outstanding;
}

bool jfc::wanikani_reviews_icon::request::pump() {
    if (!g_pSession) return false;

    const bool handled = g_pSession->pContext->main_try_handle_completed_request();

    if (handled && g_pSession->outstanding) --g_pSession->outstanding;

    return handled;
}

void jfc::wanikani_reviews_icon::request::shutdown() {
    if (!g_pSession) return;

    g_pSession->pContext->cancel_all();
    g_pSession.reset();
}
