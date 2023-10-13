cmake_minimum_required(VERSION 3.14)

project(SpatialAccelerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Eigen - Header only library
include_directories(libs/eigen-3.4.0)

# Google Test
add_subdirectory(libs/googletest-1.14.0)
enable_testing()
include_directories(
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
)

# build Spatial Accelerator
add_executable(
    spatial_accelerator
    src/main.cpp
)

# Test Executable
add_executable(runTests tests/test_souffle.cpp)

# Link test executable with Google Test
target_link_libraries(
    runTests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)


