#include "../Day2/FindResult.h"
#include "../Day2/Split.cpp"
#include "../Day2/findWordOnGrid.cpp"
#include "../Day2/pointsToIntMap.cpp"

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
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

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
    char grid[][6]{
        {'F', 'F', 'E', 'S', 'D', 'R'},
        {'F', 'F', 'K', 'S', 'D', 'R'},
        {'F', 'F', 'Q', 'S', 'D', 'R'},
        {'F', 'I', 'E', 'I', 'D', 'R'},
        {'F', 'F', 'E', 'D', 'D', 'R'}
    };;
    const std::string wordToFind{"FESSS"};

    FindResult actual = Day2::findWordOnGrid(6, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == false);
    REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::IsEmpty());
}

TEST_CASE("FindWordOnGrid finds single letter words", "[findWordOnGrid]") {
    char grid[][6]{
        {'F', 'F', 'E', 'S', 'D', 'R'},
        {'F', 'F', 'K', 'S', 'D', 'R'},
        {'F', 'F', 'Q', 'S', 'D', 'R'},
        {'F', 'I', 'E', 'I', 'D', 'R'},
        {'F', 'F', 'E', 'D', 'D', 'R'}
    };
    auto [wordToFind, branch] = GENERATE(table<std::string, int>({
                                             std::make_tuple("F", 0),
                                             std::make_tuple("K", 1),
                                             std::make_tuple("S", 2),
                                             std::make_tuple("E", 3),
                                             std::make_tuple("D", 4),
                                             std::make_tuple("R", 5),
                                             std::make_tuple("I", 6),
                                             std::make_tuple("Q", 7)
                                             }));
    SECTION(wordToFind) {
        std::vector<Point> expected;
        switch (branch) {
            case 0:
                expected = {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}, {0, 3}, {0, 4}, {1, 4}};
                break;
            case 1:
                expected = {{2, 1}};
                break;
            case 2:
                expected = {{3, 0}, {3, 1}, {3, 2}};
                break;
            case 3:
                expected = {{2, 0}, {2, 3}, {2, 4}};
                break;
            case 4:
                expected = {{4, 0}, {4, 1}, {4, 2}, {4, 3}, {3, 4}, {4, 4}};
                break;
            case 5:
                expected = {{5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}};
                break;
            case 6:
                expected = {{1, 3}, {3, 3}};
                break;
            case 7:
                expected = {{2, 2}};
                break;
            default:
                std::cout << "TILT" << std::endl;
                Catch::throw_test_failure_exception();
        }

        FindResult actual = Day2::findWordOnGrid(6, 5, reinterpret_cast<char *>(grid), wordToFind);

        REQUIRE(actual.found == true);
        REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEST_CASE("FindWordOnGrid finds single word", "[findWordOnGrid]") {
    char grid[][6]{
        {'F', 'F', 'E', 'S', 'D', 'R'},
        {'F', 'F', 'K', 'S', 'D', 'R'},
        {'F', 'F', 'Q', 'S', 'D', 'R'},
        {'F', 'I', 'E', 'I', 'D', 'R'},
        {'F', 'F', 'E', 'D', 'D', 'R'}
    };
    auto [testName, wordToFind, direction] = GENERATE(table<std::string, std::string, int>(
                                                          {
                                                          std::make_tuple("Left to Right","FES",0),
                                                          std::make_tuple("Right to Left","SEF",0),
                                                          std::make_tuple("Down","SID",1),
                                                          std::make_tuple("Up","DIS",1),
                                                          std::make_tuple("Left Wrap","DRFI",2),
                                                          std::make_tuple("Right Wrap","IFRD",2)
                                                          }));
    SECTION(testName) {
        std::vector<Point> expected;
        switch (direction) {
            case 0: expected = {{1, 0}, {2, 0}, {3, 0}};
                break;
            case 1: expected = {{3, 2}, {3, 3}, {3, 4}};
                break;
            case 2: expected = {{4, 3}, {5, 3}, {0, 3}, {1, 3}};
                break;
            default:
                std::cout << "TILT" << std::endl;
                Catch::throw_test_failure_exception();
        }

        FindResult actual = Day2::findWordOnGrid(6, 5, reinterpret_cast<char *>(grid), wordToFind);

        REQUIRE(actual.found == true);
        REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEST_CASE("FindWordOnGrid doesnt find sneaky letters", "[findWordOnGrid]") {
    char grid[][6]{
        {'F', 'F', 'E', 'S', 'D', 'R'},
        {'F', 'F', 'K', 'S', 'S', 'R'},
        {'F', 'F', 'Q', 'S', 'D', 'R'},
        {'F', 'I', 'E', 'I', 'D', 'R'},
        {'F', 'F', 'E', 'D', 'D', 'R'}
    };
    std::string wordToFind = "SSI";
    std::vector<Point> expected{{3, 1}, {3, 2}, {3, 3}};

    FindResult actual = Day2::findWordOnGrid(6, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == true);
    REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
}

TEST_CASE("FindWordOnGrid finds multiple overlapping words", "[findWordOnGrid]") {
    char grid[][6]{
        {'F', 'F', 'E', 'S', 'D', 'R'},
        {'F', 'F', 'K', 'S', 'D', 'R'},
        {'F', 'F', 'Q', 'S', 'D', 'R'},
        {'F', 'I', 'E', 'I', 'F', 'F'},
        {'F', 'F', 'E', 'D', 'D', 'R'}
    };
    const std::string wordToFind{"FF"};

    std::vector<Point> expected{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}, {0, 3}, {4, 3}, {5, 3}, {0, 4}, {1, 4}};

    FindResult actual = Day2::findWordOnGrid(6, 5, reinterpret_cast<char *>(grid), wordToFind);

    REQUIRE(actual.found == true);
    REQUIRE_THAT(actual.symbolLocations, Catch::Matchers::UnorderedRangeEquals(expected));
}
#pragma endregion findWordOnGrid

#pragma region pointsToIntMap
TEST_CASE("PointsToIntMap maps points accurately to int map", "[pointsToIntMap]") {
    std::vector<Point> input{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}, {0, 3}, {4, 3}, {0, 4}, {1, 4}};
    std::vector<std::vector<bool> > expected = {
        {true, true, true, true, true},
        {true, true, true, false, true},
        {false, false, false, false, false},
        {false, false, false, false, false},
        {false, false, false, true, false},
    };

    std::vector<std::vector<bool> > actual = Day2::pointsToIntMap(input, 5, 5);

    REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
}
#pragma endregion pointsToIntMap

#pragma region orMap
TEST_CASE("OrMap adds two maps together", "[orMap]") {
    std::vector<std::vector<bool> > map1 = {
        {true, true, true, true, true},
        {true, true, true, false, true},
        {false, false, false, false, false},
        {false, false, false, false, false},
        {false, false, true, true, false},
    };
    std::vector<std::vector<bool> > map2 = {
        {true, true, true, true, true},
        {true, true, true, false, true},
        {false, false, false, false, false},
        {false, false, false, false, false},
        {false, true, false, true, false},
    };
    std::vector<std::vector<bool> > expected = {
        {true, true, true, true, true},
        {true, true, true, false, true},
        {false, false, false, false, false},
        {false, false, false, false, false},
        {false, true, true, true, false},
    };

    std::vector<std::vector<bool> > actual = Day2::orMap(map1, map2, 5, 5);

    REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
}
#pragma endregion orMap

