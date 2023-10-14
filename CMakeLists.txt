cmake_minimum_required(VERSION 3.14)

project(SpatialAccelerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###--> Configuration and Verification
# Include Config
if(EXISTS "${CMAKE_SOURCE_DIR}/config.cmake")
    include("${CMAKE_SOURCE_DIR}/config.cmake")
endif()

# Verify required config
if(NOT DEFINED VTK_DIR)
    message(FATAL_ERROR "VTK_DIR is not defined. Please specify the VTK directory.")
endif()

# Check for required libraries
set(REQUIRED_SUBDIRS
    eigen-3.4.0
    googletest-1.14.0
)

foreach(subdir ${REQUIRED_SUBDIRS})
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/${subdir}")
        message(FATAL_ERROR "Required subdirectory ${subdir} does not exist in the libs folder!")
    endif()
endforeach()

###--> Add libraries
# Eigen - Header only library
include_directories(libs/eigen-3.4.0)

# Google Test
# Switch off GMOCK
set(BUILD_GMOCK OFF CACHE BOOL "Don't build gmock" FORCE)

add_subdirectory(libs/googletest-1.14.0)
enable_testing()
# include_directories(
#     ${gtest_SOURCE_DIR}/include
#     ${gtest_SOURCE_DIR}
# )

# VTK
find_package(VTK COMPONENTS
    CommonColor
    CommonCore
    FiltersSources
    InteractionStyle
    RenderingContextOpenGL2
    RenderingCore
    RenderingFreeType
    RenderingGL2PSOpenGL2
    RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "CylinderExample: Unable to find the VTK build folder.")
endif()

###--> Define Executables

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(CylinderExample MACOSX_BUNDLE src/cylinder_example.cpp )
  target_link_libraries(CylinderExample PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS CylinderExample
  MODULES ${VTK_LIBRARIES}
)

# build Spatial Accelerator
add_executable(
    spatial_accelerator
    src/main.cpp
)

# Test Executable
add_executable(run_tests
    tests/test_spatial_hashing.cpp
)
target_include_directories(run_tests
    PUBLIC ${CMAKE_SOURCE_DIR}/src
)

# Link test executable with Google Test
target_link_libraries(
    run_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)