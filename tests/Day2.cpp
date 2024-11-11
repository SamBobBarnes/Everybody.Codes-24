#include <catch2/catch_test_macros.hpp>
#include "../Day2/Split.cpp"

TEST_CASE("Split converts string into list of strings", "[split]") {
    const std::vector<std::string> expected{"Hello", "my", "favorite", "wonderful", "World!"};
    const std::string input{"Hello my favorite wonderful World!"};

    REQUIRE(Day2::split(input) == expected);
}

TEST_CASE("Split converts string into list of strings without blanks", "[split]") {
    const std::vector<std::string> expected{"Hello", "my", "favorite", "wonderful", "World!"};
    const std::string input{"Hello  my  favorite  wonderful  World!"};

    REQUIRE(Day2::split(input) == expected);
}

TEST_CASE("Split converts string with no spaces into list of single string", "[split]") {
    const std::vector<std::string> expected{"Hello!"};
    const std::string input{"Hello!"};

    REQUIRE(Day2::split(input) == expected);
}
