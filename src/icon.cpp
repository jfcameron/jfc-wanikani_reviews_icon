// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/config.h>
#include <jfc/wanikani_reviews_icon/icon.h>
#include <jfc/wanikani_reviews_icon/icons.h>

#include <gtk/gtk.h>

#include <gio/gio.h>

#include <pango/pangocairo.h>

#include JFC_APPINDICATOR_HEADER

#include <cstdlib>
#include <filesystem>
#include <system_error>
#include <mutex>
#include <optional>
#include <set>
#include <string>

using namespace jfc::wanikani_reviews_icon;

namespace {
    constexpr const char *APPLICATION_ID = "io.github.jfcameron.wanikani_reviews_icon";
    constexpr const char *WANIKANI_URL = "https://www.wanikani.com/";

    AppIndicator *pIndicator = nullptr;

    void open_wanikani() {
        const std::string command(config::get_browser_command());

        if (command.empty()) {
            GError *pError = nullptr;

            if (!g_app_info_launch_default_for_uri(WANIKANI_URL, nullptr, &pError)) {
                g_warning("could not open %s: %s", WANIKANI_URL, pError ? pError->message : "unknown error");

                if (pError) g_error_free(pError);
            }

            return;
        }

        gchar **ppArgv = nullptr;
        GError *pError = nullptr;

        if (!g_shell_parse_argv(command.c_str(), nullptr, &ppArgv, &pError)) {
            g_warning("could not read browser_command \"%s\" from the config file: %s",
                command.c_str(), pError ? pError->message : "unknown error");

            if (pError) g_error_free(pError);

            return;
        }

        const guint count = g_strv_length(ppArgv);

        ppArgv = g_renew(gchar *, ppArgv, count + 2);
        ppArgv[count] = g_strdup(WANIKANI_URL);
        ppArgv[count + 1] = nullptr;

        if (!g_spawn_async(nullptr, ppArgv, nullptr,
            static_cast<GSpawnFlags>(G_SPAWN_SEARCH_PATH | G_SPAWN_STDOUT_TO_DEV_NULL | G_SPAWN_STDERR_TO_DEV_NULL),
            nullptr, nullptr, nullptr, &pError)
        ) {
            g_warning("could not launch \"%s\": %s", command.c_str(),
                pError ? pError->message : "unknown error");

            if (pError) g_error_free(pError);
        }

        g_strfreev(ppArgv);
    }

    [[nodiscard]] std::string icon_directory() {
        if (const char *const runtime = std::getenv("XDG_RUNTIME_DIR"); runtime && *runtime)
            return std::string(runtime) + "/" + APPLICATION_ID + "/";

        return std::string(g_get_user_config_dir()) + "/wanikani_reviews_icon/icons/";
    }

    [[nodiscard]] const char *icon_name(const icon::graphic aGraphic) {
        switch (aGraphic) {
            case icon::graphic::init:         return "wanikani-init";
            case icon::graphic::disconnected: return "wanikani-no-connection";
            case icon::graphic::reviews:      return "wanikani-reviews";
            case icon::graphic::no_reviews:   return "wanikani-no-reviews";
        }

        return "wanikani-init";
    }

    void write_icon(const std::string &aDirectory, const char *const aName, GdkPixbuf *const apPixbuf) {
        if (!apPixbuf) return;

        const std::string path(aDirectory + aName + ".png");

        GError *pError = nullptr;

        if (!gdk_pixbuf_save(apPixbuf, path.c_str(), "png", &pError, nullptr)) {
            g_warning("could not write the tray icon %s: %s", path.c_str(),
                pError ? pError->message : "unknown error");

            if (pError) g_error_free(pError);
        }
    }

    [[nodiscard]] GtkWidget *build_menu() {
        GtkWidget *const pMenu = gtk_menu_new();

        GtkWidget *const pOpen = gtk_menu_item_new_with_label("Open WaniKani");

        g_signal_connect(pOpen, "activate", G_CALLBACK(+[](GtkMenuItem *, gpointer) {
            open_wanikani();
        }), nullptr);

        gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pOpen);

        GtkWidget *const pQuit = gtk_menu_item_new_with_label("Quit");

        g_signal_connect(pQuit, "activate", G_CALLBACK(+[](GtkMenuItem *, gpointer) {
            gtk_main_quit();
        }), nullptr);

        gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pQuit);

        gtk_widget_show_all(pMenu);

        return pMenu;
    }

    std::set<std::string> writtenIcons;
    std::string badgedIconOnDisk;
    icon::graphic currentGraphic = icon::graphic::init;
    std::optional<std::size_t> currentBadge;

    [[nodiscard]] GdkPixbuf *with_badge(GdkPixbuf *const apBase, const std::size_t aCount) {
        const int width = gdk_pixbuf_get_width(apBase);
        const int height = gdk_pixbuf_get_height(apBase);

        cairo_surface_t *const pSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

        cairo_t *const pCairo = cairo_create(pSurface);

        gdk_cairo_set_source_pixbuf(pCairo, apBase, 0, 0);
        cairo_paint(pCairo);

        const std::string text(aCount > 99 ? "99+" : std::to_string(aCount));

        PangoLayout *const pLayout = pango_cairo_create_layout(pCairo);

        PangoFontDescription *const pFont = pango_font_description_from_string(
            text.size() > 2 
                ? "Sans Bold 10" 
                : "Sans Bold 13"
        );

        pango_layout_set_font_description(pLayout, pFont);
        pango_layout_set_text(pLayout, text.c_str(), -1);

        int textWidth = 0;
        int textHeight = 0;

        pango_layout_get_pixel_size(pLayout, &textWidth, &textHeight);

        const double x = (width - textWidth) / 2.0;
        const double y = height - textHeight;

        cairo_move_to(pCairo, x, y);
        pango_cairo_layout_path(pCairo, pLayout);

        cairo_set_line_width(pCairo, 2.5);
        cairo_set_line_join(pCairo, CAIRO_LINE_JOIN_ROUND);
        cairo_set_source_rgba(pCairo, 0.0, 0.0, 0.0, 0.85);
        cairo_stroke_preserve(pCairo);

        cairo_set_source_rgb(pCairo, 1.0, 1.0, 1.0);
        cairo_fill(pCairo);

        GdkPixbuf *const pResult = gdk_pixbuf_get_from_surface(pSurface, 0, 0, width, height);

        pango_font_description_free(pFont);
        g_object_unref(pLayout);
        cairo_destroy(pCairo);
        cairo_surface_destroy(pSurface);

        return pResult;
    }

    [[nodiscard]] GdkPixbuf *base_pixbuf(const icon::graphic aGraphic) {
        switch (aGraphic) {
            case icon::graphic::init:         return jfc::get_init_image();
            case icon::graphic::disconnected: return jfc::get_no_connection_image();
            case icon::graphic::reviews:      return jfc::get_reviews_available_image();
            case icon::graphic::no_reviews:   return jfc::get_reviews_complete_image();
        }

        return jfc::get_init_image();
    }

    void init_once();

    [[nodiscard]] std::string hover_text() {
        switch (currentGraphic) {
            case icon::graphic::disconnected: return "WaniKani: disconnected";
            case icon::graphic::no_reviews:   return "WaniKani: no reviews";
            case icon::graphic::reviews:
                if (currentBadge) return "WaniKani: " + std::to_string(*currentBadge)
                    + (*currentBadge == 1 ? " review" : " reviews");

                return "WaniKani: reviews available";

            case icon::graphic::init: break;
        }

        return "WaniKani reviews";
    }

    void refresh() {
        init_once();

        std::string name(icon_name(currentGraphic));

        if (currentBadge) name += "-" + std::to_string(*currentBadge > 99 ? 99 : *currentBadge)
            + (*currentBadge > 99 ? "plus" : "");

        if (!writtenIcons.count(name)) {
            GdkPixbuf *const pBase = base_pixbuf(currentGraphic);

            if (currentBadge) {
                GdkPixbuf *const pBadged = with_badge(pBase, *currentBadge);

                write_icon(icon_directory(), name.c_str(), pBadged);

                g_object_unref(pBadged);
            }
            else write_icon(icon_directory(), name.c_str(), pBase);

            writtenIcons.insert(name);

            if (currentBadge) {
                if (!badgedIconOnDisk.empty() && badgedIconOnDisk != name) {
                    std::error_code ignored;

                    std::filesystem::remove(icon_directory() + badgedIconOnDisk + ".png", ignored);

                    writtenIcons.erase(badgedIconOnDisk);
                }

                badgedIconOnDisk = name;
            }
        }

        app_indicator_set_icon_full(pIndicator, name.c_str(), "WaniKani reviews");
        app_indicator_set_title(pIndicator, hover_text().c_str());
    }

    void init_once() {
        static std::once_flag flag;

        std::call_once(flag, []() {
            const std::string directory(icon_directory());

            g_mkdir_with_parents(directory.c_str(), 0700);

            write_icon(directory, "wanikani-init", jfc::get_init_image());

            writtenIcons.insert("wanikani-init");

            pIndicator = app_indicator_new(APPLICATION_ID, "wanikani-init",
                APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

            app_indicator_set_icon_theme_path(pIndicator, directory.c_str());

            app_indicator_set_menu(pIndicator, GTK_MENU(build_menu()));

            app_indicator_set_status(pIndicator, APP_INDICATOR_STATUS_ACTIVE);
        });
    }
}

void jfc::wanikani_reviews_icon::icon::set_graphic(jfc::wanikani_reviews_icon::icon::graphic a) {
    currentGraphic = a;
    refresh();
}

void jfc::wanikani_reviews_icon::icon::set_badge(std::optional<std::size_t> aCount) {
    currentBadge = aCount;
    refresh();
}
