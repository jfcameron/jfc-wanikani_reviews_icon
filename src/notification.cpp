// © 2020 Joseph Cameron - All Rights Reserved
#include <jfc/wanikani_reviews_icon/notification.h>

#include <iostream>
#include <mutex>
#include <string>

#include <gtk/gtk.h>

using namespace jfc::wanikani_reviews_icon::notify;

static GApplication *pApplication;

static GNotification *pNotification;

void static init_once()
{
    static std::once_flag flag;

    std::call_once(flag, []()
    {
        pApplication = []()
        {
            auto p = (g_application_new("jfcameron.github.wanikani_reviews_icon", G_APPLICATION_FLAGS_NONE));
            
            return p ? p : throw std::runtime_error("could not initialize the g_application");
        }();

        pNotification = []()
        {
            auto p = (g_notification_new("Build failed"));

            return p ? p : throw std::runtime_error("could not initialize g_notification");
        }();

        g_application_register(pApplication, nullptr, nullptr);

        g_notification_set_default_action(pNotification, "app.new.reviews");
    });
}

void jfc::wanikani_reviews_icon::notify::review_count_changed(size_t count)
{
    init_once();

    g_notification_set_title(pNotification, "Wanikani: new reviews");

    g_notification_set_body(pNotification, std::to_string(count).c_str());

    g_application_send_notification(pApplication, "notification", pNotification);
}

