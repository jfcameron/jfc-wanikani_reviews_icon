// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_NOTIFICATION_H
#define JFC_WANIKANI_NOTIFICATION_H

#include <string>

/// \brief functions used to communicate state changes to the user via notifications
namespace jfc::wanikani_reviews_icon::notify {
    /// \brief tell the user the number of waiting reviews has gone up
    void review_count_changed(size_t count);
}

#endif

