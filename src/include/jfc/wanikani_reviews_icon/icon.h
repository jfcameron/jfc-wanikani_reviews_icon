// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_ICON_H
#define JFC_WANIKANI_ICON_H

#include <string>

/// \brief functions used to manipulate the system tray icon
///
/// \warn gtk_init must be called before using any function declared in this namespace
namespace jfc::wanikani_reviews_icon::icon
{
    enum class graphic
    {
        init,
        disconnected,
        reviews,
        no_reviews
    };

    /// \brief changes icon graphic given a number of reviews
    void set_graphic(graphic a);

    /// \brief changes the icon tool tip. 
    ///
    /// \note tool tip is displayed when user holds the cursor over the icon
    void set_tooltip(const std::string &aToolTip);
}

#endif

