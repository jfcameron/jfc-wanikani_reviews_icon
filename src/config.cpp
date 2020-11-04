// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/config.h>

#include <wanikani_reviews_icon/buildinfo.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace jfc::wanikani_reviews_icon;

namespace fs = std::filesystem;

static std::string wanikani_token = "";

// Try to give a reasonable default browser command. 
static std::string browser_command = 
#if defined JFC_TARGET_PLATFORM_Linux
    "xdg-open";
#elif defined JFC_TARGET_PLATFORM_Darwin
    "open";
#else
    "firefox";
#endif

std::string jfc::wanikani_reviews_icon::config::get_wanikani_token()
{
    return wanikani_token;
}

std::string jfc::wanikani_reviews_icon::config::get_browser_command()
{
    return browser_command;
}

// Path to the config file will vary if non POSIX platforms are supported
const std::string config_directory =
#if defined JFC_TARGET_PLATFORM_Linux || defined JFC_TARGET_PLATFORM_Darwin //...
    std::string(std::getenv("HOME")).append("/.config/wanikani_reviews_icon/");
//#elif defined JFC_TARGET_PLATFORM_Windows
    //windows api to get user's appdata path...
#else
#error "unsupported platform"
#endif

static const std::string config_filename("conf.json");

static const std::string config_path(config_directory + config_filename);
    
using namespace nlohmann;

void jfc::wanikani_reviews_icon::config::load_config_file()
{
    if (!fs::exists(config_path)) 
    {
        std::cout << "Creating config file: \"" + config_path + "\n";

        save_config_file();
    }

    std::ifstream ifs(config_path);

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    try
    {
        auto root = json::parse(content);

        // Deserialization
        wanikani_token = root["wanikani_token"];
        browser_command = root["browser_command"];

        std::string error_string;

        if (wanikani_token.empty()) error_string += "Config file does not contain a wanikani token. "
            "A token is required in order to list your travis-ci builds. "
            "A token can be generated after logging into the wanikani website. "
            "Please add a valid token to the config file.";

        if (!error_string.empty()) throw std::invalid_argument(error_string);
    }
    catch (nlohmann::detail::parse_error e)
    {
        throw std::invalid_argument(std::string("Parsing error while loading the config file.")
            .append(" Path: {") + config_path + "}, Parsing error: {" + e.what() + "}");
    }
}

void jfc::wanikani_reviews_icon::config::save_config_file()
{
    fs::create_directories(config_directory);
    
    std::ofstream ofs(config_path);

    json root;

    // Serialization
    root["wanikani_token"] = wanikani_token;
    root["browser_command"] = browser_command;

    ofs << root.dump(4, ' ');
}

