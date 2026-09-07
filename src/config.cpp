// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/config.h>

#include <wanikani_reviews_icon/buildinfo.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include <pwd.h>
#include <unistd.h>

#include <nlohmann/json.hpp>

using namespace jfc::wanikani_reviews_icon;

namespace fs = std::filesystem;

static std::string wanikani_token = "";

static std::string browser_command = 
#if defined JFC_TARGET_PLATFORM_Linux
    "xdg-open";
#elif defined JFC_TARGET_PLATFORM_Darwin
    "open";
#endif

std::string jfc::wanikani_reviews_icon::config::get_wanikani_token() {
    return wanikani_token;
}

std::string jfc::wanikani_reviews_icon::config::get_browser_command() {
    return browser_command;
}

static const std::string config_filename("conf.json");

namespace {
    [[nodiscard]] std::string find_config_directory() {
        if (const char *const xdg = std::getenv("XDG_CONFIG_HOME"); xdg && *xdg)
            return std::string(xdg) + "/wanikani_reviews_icon/";

        if (const char *const home = std::getenv("HOME"); home && *home)
            return std::string(home) + "/.config/wanikani_reviews_icon/";

        if (const passwd *const pw = ::getpwuid(::getuid()); pw && pw->pw_dir && *pw->pw_dir)
            return std::string(pw->pw_dir) + "/.config/wanikani_reviews_icon/";

        throw std::runtime_error("could not determine a configuration directory: neither "
            "XDG_CONFIG_HOME nor HOME is set, and this user has no home directory on record");
    }

    [[nodiscard]] const std::string &config_directory() {
        static const std::string value(find_config_directory());

        return value;
    }

    [[nodiscard]] const std::string &config_path() {
        static const std::string value(config_directory() + config_filename);

        return value;
    }

    void restrict_to_owner(const fs::path &aPath) {
        std::error_code error;

        const auto status = fs::status(aPath, error);

        if (error) return;

        constexpr auto OWNER_ONLY = fs::perms::owner_read | fs::perms::owner_write;

        if ((status.permissions() & ~OWNER_ONLY) == fs::perms::none) return;

        fs::permissions(aPath, OWNER_ONLY, fs::perm_options::replace, error);

        if (!error) std::cout << "Restricted permissions on " << aPath.string()
            << " to owner read/write, because it holds an api token.\n";
    }
}
    
using namespace nlohmann;

void jfc::wanikani_reviews_icon::config::load_config_file() {
    if (!fs::exists(config_path())) {
        std::cout << "Creating config file: \"" + config_path() + "\"\n";
        save_config_file();
    }

    restrict_to_owner(config_path());

    std::ifstream ifs(config_path());

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    try {
        auto root = json::parse(content);

        wanikani_token = root.value("wanikani_token", std::string());
        browser_command = root.value("browser_command", browser_command);

        std::string error_string;

        if (wanikani_token.empty()) error_string += 
            "Config file does not contain a wanikani token. "
            "A token is required in order to read your review summary. "
            "A token can be generated after logging into the wanikani website. "
            "Please add a valid token to the config file.";

        if (!error_string.empty()) throw std::invalid_argument(error_string);
    }

    catch (const nlohmann::json::exception &e) {
        throw std::invalid_argument(std::string("Could not read the config file.")
            .append(" Path: {") + config_path() + "}, error: {" + e.what() + "}");
    }
}

void jfc::wanikani_reviews_icon::config::save_config_file() {
    fs::create_directories(config_directory());

    std::error_code error;

    fs::permissions(config_directory(), fs::perms::owner_all, fs::perm_options::replace, error);

    { 
        const std::ofstream create(config_path(), std::ios::app); 
    }

    restrict_to_owner(config_path());

    std::ofstream ofs(config_path(), std::ios::trunc);

    json root;

    root["wanikani_token"] = wanikani_token;
    root["browser_command"] = browser_command;

    ofs << root.dump(4, ' ');
}

