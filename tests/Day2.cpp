#include "PointMatcher.h"
#include "../Day2/FindResult.h"
#include "../Day2/Split.cpp"
#include "../Day2/findWordOnGrid.cpp"

#pragma region Stringify
std::ostream &operator <<(std::ostream &os, Point const &value) {
    os << value.x << "," << value.y;
    return os;
}
#pragma endregion Stringify

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#pragma region Split
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
#pragma endregion Split

#pragma region findWordOnGrid
TEST_CASE("FindWordOnGrid does not find word", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'F', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };;
    const std::string wordToFind{"FESSS"};

    FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == false);
    REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::IsEmpty());
}

TEST_CASE("FindWordOnGrid finds single word horizontal LR", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'F', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };;
    const std::string wordToFind{"FES"};

    const std::vector<Point> expected{{1, 0}, {2, 0}, {3, 0}};

    FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == true);
    // REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    REQUIRE(compareVectors(actual.symbolLocations,expected));
}

TEST_CASE("FindWordOnGrid finds single word horizontal RL", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'F', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };;
    const std::string wordToFind{"SEF"};

    const std::vector<Point> expected{{1, 0}, {2, 0}, {3, 0}};

    FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == true);
    // REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    REQUIRE(compareVectors(actual.symbolLocations,expected));
}

TEST_CASE("FindWordOnGrid finds single word vertical TB", "[findWordOnGrid]") {
}

TEST_CASE("FindWordOnGrid finds single word vertical BT", "[findWordOnGrid]") {
}

TEST_CASE("FindWordOnGrid finds single word wrapped around right side", "[findWordOnGrid]") {
}

TEST_CASE("FindWordOnGrid finds single word wrapped around left side", "[findWordOnGrid]") {
}
#pragma endregion findWordOnGrid

