cmake_minimum_required(VERSION 3.14)

project(SpatialAccelerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Eigen - Header only library
# include_directories(libs/eigen-3.4.0)

# # Google Test
# set(gtest_SOURCE_DIR "libs/googletest-1.14.0")
# add_subdirectory(${gtest_SOURCE_DIR})
# enable_testing()
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# # Main Executable
# add_executable(SpatialAccelerator src/main.cpp)

# # Test Executable
# add_executable(runTests tests/test_souffle.cpp)

# # Link test executable with Google Test
# target_link_libraries(runTests gtest gtest_main)

# # Add test
# include (GoogleTest)
# gtest_discover_tests(runTests)


# TUTORIAL HANDLING FOR GTEST
# include(FetchContent)
# # FetchContent_Declare(
# #   googletest
# #   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# # )

# FetchContent_Declare(
#     googletest
#     SOURCE_DIR libs/googletest
# )

# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)



# # Main Executable
# add_executable(SpatialAccelerator src/main.cpp)

# # Test Executable
# add_executable(runTests tests/test_souffle.cpp)

# # Link test executable with Google Test
# target_link_libraries(
#     runTests
#     GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(runTests)

# set(gtest_SOURCE_DIR "libs/googletest-1.14.0")
# set(gtest_SOURCE_DIR "libs/googletest")
# add_subdirectory(${gtest_SOURCE_DIR})
# include_directories(
#     ${gtest_SOURCE_DIR}
# )


# include(FetchContent)
# FetchContent_Declare(
#     googletest
#     SOURCE_DIR ${gtest_SOURCE_DIR}
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)






# # Test Executable
# add_executable(runTests tests/test_souffle.cpp)

# # Link test executable with Google Test
# target_link_libraries(
#     runTests
#     GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(runTests)


add_subdirectory(libs/googletest-1.14.0)
enable_testing()
include_directories(
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
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


