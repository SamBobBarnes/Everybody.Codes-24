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
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'I', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };;
    const std::string wordToFind{"FESSS"};

    FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == false);
    REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::IsEmpty());
}

TEST_CASE("FindWordOnGrid finds single word", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'I', 'E', 'I', 'D'},
        {'F', 'F', 'E', 'D', 'D'}
    };
    std::string testName;
    std::string wordToFind;
    int direction;
    std::tie(testName, wordToFind, direction) = GENERATE(table<std::string, std::string, int>(
                                                             {
                                                             std::make_tuple("Left to Right","FES",0),
                                                             std::make_tuple("Right to Left","SEF",0),
                                                             std::make_tuple("Down","SID",1),
                                                             std::make_tuple("Up","DIS",1),
                                                             std::make_tuple("Left Wrap","DFI",2),
                                                             std::make_tuple("Right Wrap","IFD",2)
                                                             }));
    SECTION(testName) {
        std::vector<Point> expected;
        switch (direction) {
            case 0: expected = {{1, 0}, {2, 0}, {3, 0}};
                break;
            case 1: expected = {{3, 2}, {3, 3}, {3, 4}};
                break;
            case 2: expected = {{4, 3}, {0, 3}, {1, 3}};
                break;
            default:
                std::cout << "TILT" << std::endl;
                Catch::throw_test_failure_exception();
        }

        FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

        REQUIRE(actual.found == true);
        REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEST_CASE("FindWordOnGrid finds multiple overlapping words", "[findWordOnGrid]") {
    char grid[][5]{
        {'F', 'F', 'E', 'S', 'D'}, {'F', 'F', 'K', 'S', 'D'}, {'F', 'F', 'Q', 'S', 'D'}, {'F', 'I', 'E', 'I', 'F'},
        {'F', 'F', 'E', 'D', 'D'}
    };
    const std::string wordToFind{"FF"};

    std::vector<Point> expected{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}, {0, 3}, {4, 3}, {0, 4}, {1, 4}};

    FindResult actual = Day2::findWordOnGrid(5, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == true);
    REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
}
#pragma endregion findWordOnGrid

