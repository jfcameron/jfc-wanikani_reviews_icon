// © 2020 Joseph Cameron - All Rights Reserved

#ifndef JFC_WANIKANI_SUMMARY_H
#define JFC_WANIKANI_SUMMARY_H

#include <cstddef>
#include <optional>
#include <vector>

/// \brief reading the wanikani summary payload
namespace jfc::wanikani_reviews_icon::summary {
    /// \brief how many reviews the payload says are waiting, or nothing if it cannot be read
    [[nodiscard]] std::optional<std::size_t> review_count(const std::vector<unsigned char> &aBody);
}

#endif
