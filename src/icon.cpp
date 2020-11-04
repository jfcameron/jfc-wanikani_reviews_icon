// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/config.h>
#include <jfc/wanikani_reviews_icon/icon.h>
#include <jfc/wanikani_reviews_icon/icons.h>

#include <gtk/gtk.h>

#include <mutex>
#include <iostream>

using namespace jfc::wanikani_reviews_icon;

static GtkStatusIcon *tray_icon;

static void init_once()
{
    static bool once(true);

    if (once)
    {
        once = false;

        tray_icon = gtk_status_icon_new();

        gtk_status_icon_set_visible (tray_icon, TRUE);

        g_signal_connect(G_OBJECT(tray_icon), 
            "activate", 
            G_CALLBACK([](){
                system(std::string(config::get_browser_command())
                    .append(" ")
                    .append("https://www.wanikani.com/")
                    .c_str());}),
            nullptr
        );
    }

    return;
}

void jfc::wanikani_reviews_icon::icon::set_graphic(jfc::wanikani_reviews_icon::icon::graphic a)
{
    init_once();

    switch (a)
    {
        case (jfc::wanikani_reviews_icon::icon::graphic::init):
            gtk_status_icon_set_from_pixbuf(tray_icon, jfc::get_init_image()); 
            return;
        case (jfc::wanikani_reviews_icon::icon::graphic::disconnected):
            gtk_status_icon_set_from_pixbuf(tray_icon, jfc::get_no_connection_image()); 
            return;
        case (jfc::wanikani_reviews_icon::icon::graphic::reviews):
            gtk_status_icon_set_from_pixbuf(tray_icon, jfc::get_reviews_available_image()); 
            return;
        case (jfc::wanikani_reviews_icon::icon::graphic::no_reviews):
            gtk_status_icon_set_from_pixbuf(tray_icon, jfc::get_reviews_complete_image()); 
            return;
    }
}

void jfc::wanikani_reviews_icon::icon::set_tooltip(const std::string &aToolTip)
{
    init_once();

    gtk_status_icon_set_tooltip_text(tray_icon, aToolTip.c_str());
}

