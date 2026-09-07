// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/wanikani_reviews_icon/summary.h>

#include <nlohmann/json.hpp>

#include <exception>

std::optional<std::size_t> jfc::wanikani_reviews_icon::summary::review_count(const std::vector<unsigned char> &aBody) {
    try {
        const nlohmann::json root = nlohmann::json::parse(aBody);
        const auto &reviews = root.at("data").at("reviews");

        if (!reviews.is_array() || reviews.empty()) return std::nullopt;

        const auto &ids = reviews[0].at("subject_ids");

        if (!ids.is_array()) return std::nullopt;

        return ids.size();
    }
    catch (const std::exception &) {
        return std::nullopt;
    }
}

