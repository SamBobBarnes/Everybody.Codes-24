find_package(Catch2 3 REQUIRED)

add_executable(tests_run Day2.cpp
        PointMatcher.h)

target_link_libraries(tests_run PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests_run)