// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_REQUEST_H
#define JFC_WANIKANI_REQUEST_H

#include <jfc/wanikani_reviews_icon/enums.h>

#include <functional>
#include <string>
#include <vector>

/// \brief fetches the wanikani account summary
namespace jfc::wanikani_reviews_icon::request
{
    using response_data_type = std::vector<unsigned char>;

    /// \brief functor type for handling successful requests
    using response_handler_type = std::function<void(response_data_type)>;

    /// \brief why a request did not produce a summary
    enum class failure {
        network,  ///< could not reach the api at all; very likely temporary
        rejected, ///< the api answered and refused, status 400 or above; very likely the token
        other     ///< anything else
    };

    /// \brief functor type for handling failed requests
    using failed_handler_type = std::function<void(failure)>;

    /// \brief ask for the account summary; returns without waiting for it
    void submit_summary(response_handler_type aSucceededHandler,
        failed_handler_type aFailedHandler);

    /// \brief run the handler for a request that has finished, if one has
    /// \return true if a handler was run
    bool pump();

    /// \brief abandon anything outstanding and release the worker thread
    void shutdown();
}

#endif
