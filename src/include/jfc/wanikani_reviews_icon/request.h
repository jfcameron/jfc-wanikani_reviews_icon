// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_REQUEST_H
#define JFC_WANIKANI_REQUEST_H

#include <jfc/wanikani_reviews_icon/enums.h>

#include <string>
#include <functional>

/// \brief functions used to interact with the travis-ci api
namespace jfc::wanikani_reviews_icon::request
{
    using response_data_type = std::vector<unsigned char>;

    /// \brief functor type for handling successful requests
    using response_handler_type = std::function<void(response_data_type)>;
    
    /// \brief functor type for handling failed requests
    using failed_handler_type = std::function<void()>;

    /// \brief retrieves a list of recent builds from the travis-ci api
    void builds(response_handler_type aSucceededHandler,
        failed_handler_type aFailedHandler);
}

#endif

