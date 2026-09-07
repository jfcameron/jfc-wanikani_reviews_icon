// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_NOTIFICATION_H
#define JFC_WANIKANI_NOTIFICATION_H

#include <jfc/wanikani_reviews_icon/enums.h>

#include <string>

/// \brief functions used to communicate state changes to the user via notifications
namespace jfc::wanikani_reviews_icon::notify {
    /// \brief notify that a build's state has changed. e.g: building to succeeded
    void review_count_changed(size_t count);
}

#endif

