// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_CONFIG_H
#define JFC_WANIKANI_CONFIG_H

#include <string>

namespace jfc::wanikani_reviews_icon::config {
    /// \brief read values from the config file
    void load_config_file();

    /// \brief write values to the config file
    void save_config_file();

    /// \brief get a copy of the wanikani api token
    std::string get_wanikani_token();

    /// \brief get a copy of the command used to open the wanikani website
    std::string get_browser_command();
}

#endif

