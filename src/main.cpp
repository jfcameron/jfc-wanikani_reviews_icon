// © 2020 Joseph Cameron - All Rights Reserved
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

#include <gtk/gtk.h>
#include <nlohmann/json.hpp>

#include <jfc/wanikani_reviews_icon/config.h>
#include <jfc/wanikani_reviews_icon/enums.h>
#include <jfc/wanikani_reviews_icon/icon.h>
#include <jfc/wanikani_reviews_icon/notification.h>
#include <jfc/wanikani_reviews_icon/request.h>

#include <wanikani_reviews_icon/buildinfo.h>

using namespace jfc::wanikani_reviews_icon;

size_t last_review_count(0);

void response_handler(std::vector<unsigned char> output)
{
    using namespace nlohmann;

    const json root = json::parse(output);

    const auto data = root["data"];

    const auto reviews = data["reviews"];

    const auto ids = reviews[0]["subject_ids"];

    const auto review_count = ids.size();
  
    // Apply tooltip text & apply icon graphic
    if (review_count) 
    {
        icon::set_tooltip(std::string("Reviews: ") + std::to_string(review_count));
        
        icon::set_graphic(icon::graphic::reviews);
    }
    else 
    {
        icon::set_tooltip("No reviews!");
        
        icon::set_graphic(icon::graphic::no_reviews);
    }

    // Notification if more reviews have become available
    if (review_count > last_review_count) notify::review_count_changed(review_count);

    last_review_count = review_count;
}

void failed_handler()
{
    icon::set_graphic(icon::graphic::disconnected);

    icon::set_tooltip("disconnected");
}

bool update()
{
    request::builds(&response_handler, &failed_handler);

    return true;
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc <= 1)
        {
            config::load_config_file();

            gtk_init(&argc, &argv);

            icon::set_graphic(icon::graphic::init);
            
            // this allows gtk_main to get called before update work starts, 
            // so the default icon will render immediately on application start
            g_timeout_add_seconds(1, [](void *const vp) 
                {
                    auto token = reinterpret_cast<std::string *>(vp);

                    update();
                    
                    g_timeout_add_seconds(60, reinterpret_cast<GSourceFunc>(update), nullptr);

                    return int(0);
                }, 
                nullptr);
           
            gtk_main();
        }
        else
        {
            std::vector<std::string> args(argv, argv + argc);

            if (args[1] == "-h" || args[1] == "--help")
            {
                std::cout
                    << "=== " << wanikani_reviews_icon_BuildInfo_ProjectName << " ===" << "\n" 
                    << "a tray icon application that notifies you of new reviews on your wanikani account.\n"
                    << "=== build info ===\n"
                    << "project remote: " << wanikani_reviews_icon_BuildInfo_Git_Remote_URL << "\n"
                    << "git hash: " << wanikani_reviews_icon_BuildInfo_Git_Commit << "\n"
                    << "build date: " << wanikani_reviews_icon_BuildInfo_Git_Date << "\n";
            }
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "error: unhandled exception" << std::endl;
    }

    return EXIT_SUCCESS;
}

