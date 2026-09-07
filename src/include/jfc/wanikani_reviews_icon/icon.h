// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_ICON_H
#define JFC_WANIKANI_ICON_H

#include <cstddef>
#include <optional>
#include <string>

/// \brief functions used to manipulate the system tray icon
namespace jfc::wanikani_reviews_icon::icon {
    enum class graphic {
        disconnected,
        init,
        no_reviews,
        reviews
    };

    /// \brief changes icon graphic given a number of reviews
    void set_graphic(graphic a);

    /// \brief show a review count on the icon itself, or nothing when there is none to show
    void set_badge(std::optional<std::size_t> aCount);
}

#endif
