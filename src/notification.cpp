// © 2020 Joseph Cameron - All Rights Reserved
#include <jfc/wanikani_reviews_icon/notification.h>

#include <iostream>
#include <mutex>
#include <string>

#include <gtk/gtk.h>

using namespace jfc::wanikani_reviews_icon::notify;

namespace {
    constexpr const char *APPLICATION_ID = "io.github.jfcameron.wanikani_reviews_icon";
}

static GApplication *pApplication;
static GNotification *pNotification;

void static init_once() {
    static std::once_flag flag;

    std::call_once(flag, []() {
        pApplication = []() {
#if GLIB_CHECK_VERSION(2, 74, 0)
            constexpr GApplicationFlags FLAGS = G_APPLICATION_DEFAULT_FLAGS;
#else
            constexpr GApplicationFlags FLAGS = G_APPLICATION_FLAGS_NONE;
#endif
            auto p = (g_application_new(APPLICATION_ID, FLAGS));
            
            return p ? p : throw std::runtime_error("could not initialize the g_application");
        }();

        pNotification = []() {
            auto p = (g_notification_new("WaniKani: new reviews"));
            return p ? p : throw std::runtime_error("could not initialize g_notification");
        }();

        g_application_register(pApplication, nullptr, nullptr);

        g_notification_set_default_action(pNotification, "app.new.reviews");
    });
}

void jfc::wanikani_reviews_icon::notify::review_count_changed(size_t count) {
    init_once();

    g_notification_set_title(pNotification, "WaniKani: new reviews");

    const std::string body(std::to_string(count) + (count == 1 ? " review available" : " reviews available"));

    g_notification_set_body(pNotification, body.c_str());

    g_application_send_notification(pApplication, "notification", pNotification);
}

