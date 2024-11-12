#include <map>

#include "../Day2/FindResult.h"
#include "../Day2/Split.cpp"
#include "../Day2/findWordOnGrid.cpp"

#pragma region Stringify
std::ostream &operator <<(std::ostream &os, Point const &value) {
    os << value.x << "," << value.y;
    return os;
}
#pragma endregion Stringify

#pragma region Comparators
bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#pragma endregion Comparators

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <catch2/generators/catch_generators_all.hpp>

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

TEST_CASE("FindWordOnGrid finds single word horizontal", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'F', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };
    std::string testName;
    std::string wordToFind;
    std::tie(testName, wordToFind) = GENERATE(table<std::string, std::string>(
                                                  {
                                                  std::make_tuple("Left to Right","FES"),
                                                  std::make_tuple("Right to Left","SEF")
                                                  }));
    SECTION(testName) {
        const std::vector<Point> expected{{1, 0}, {2, 0}, {3, 0}};

        FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

        REQUIRE(actual.found == true);
        REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEST_CASE("FindWordOnGrid finds single word vertical", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'F', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };
    std::string testName;
    std::string wordToFind;
    std::tie(testName, wordToFind) = GENERATE(table<std::string, std::string>(
                                                  {
                                                  std::make_tuple("Down","SID"),
                                                  std::make_tuple("Up","DIS")
                                                  }));
    SECTION(testName) {
        const std::vector<Point> expected{{3, 2}, {3, 3}, {3, 4}};

        FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

        REQUIRE(actual.found == true);
        REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEST_CASE("FindWordOnGrid finds single word wrapped around side", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'I', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };
    std::string testName;
    std::string wordToFind;
    std::tie(testName, wordToFind) = GENERATE(table<std::string, std::string>(
                                                  {
                                                  std::make_tuple("Left Wrap","DFI"),
                                                  std::make_tuple("Right Wrap","IFD")
                                                  }));
    SECTION(testName) {
        const std::vector<Point> expected{{4, 3}, {0, 3}, {1, 3}};

        FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

        REQUIRE(actual.found == true);
        REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}
#pragma endregion findWordOnGrid

