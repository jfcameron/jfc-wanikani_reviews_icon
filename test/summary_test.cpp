// © 2020 Joseph Cameron - All Rights Reserved

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/wanikani_reviews_icon/summary.h>

#include <string>
#include <vector>

using namespace jfc::wanikani_reviews_icon;

namespace {
    [[nodiscard]] std::vector<unsigned char> body(const std::string &aText) {
        return std::vector<unsigned char>(aText.begin(), aText.end());
    }

    [[nodiscard]] std::string summary_with(const std::size_t aCount) {
        std::string ids;

        for (std::size_t i = 0; i < aCount; ++i) ids += (i ? "," : "") + std::to_string(i);

        return R"({"data":{"reviews":[{"subject_ids":[)" + ids + R"(]}]}})";
    }
}

TEST_CASE("a well formed summary reports the number of waiting reviews",
    "[jfc::wanikani_reviews_icon::summary]") {

    REQUIRE(summary::review_count(body(summary_with(0))) == 0);
    REQUIRE(summary::review_count(body(summary_with(1))) == 1);
    REQUIRE(summary::review_count(body(summary_with(42))) == 42);
    REQUIRE(summary::review_count(body(summary_with(150))) == 150);
}

TEST_CASE("a body that cannot be read reports nothing rather than throwing",
    "[jfc::wanikani_reviews_icon::summary]") {

    SECTION("**not json at all**")
    {
        REQUIRE_FALSE(summary::review_count(body("not json")));
        REQUIRE_FALSE(summary::review_count(body("")));
        REQUIRE_FALSE(summary::review_count(body("<html>401 unauthorized</html>")));
    }

    SECTION("**json, but not an object with the fields this program reads**")
    {
        REQUIRE_FALSE(summary::review_count(body("[]")));
        REQUIRE_FALSE(summary::review_count(body("{}")));
        REQUIRE_FALSE(summary::review_count(body(R"({"error":"unauthorized"})")));
        REQUIRE_FALSE(summary::review_count(body(R"({"data":{}})")));
    }

    SECTION("**the right shape with the wrong types**")
    {
        REQUIRE_FALSE(summary::review_count(body(R"({"data":{"reviews":"soon"}})")));
        REQUIRE_FALSE(summary::review_count(body(R"({"data":{"reviews":[{"subject_ids":7}]}})")));
    }

    SECTION("**an empty list of review slots**")
    {
        REQUIRE_FALSE(summary::review_count(body(R"({"data":{"reviews":[]}})")));
    }
}

TEST_CASE("a truncated body reports nothing rather than reading past its end",
    "[jfc::wanikani_reviews_icon::summary]") {

    const std::string whole(summary_with(9));

    for (std::size_t length = 0; length < whole.size(); ++length)
    {
        const auto partial = summary::review_count(body(whole.substr(0, length)));

        INFO("truncated to " << length << " of " << whole.size() << " bytes");

        REQUIRE_FALSE(partial);
    }
}
