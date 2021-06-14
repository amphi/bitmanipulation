cmake_minimum_required(VERSION 3.15)

# Set the project name and include standard settings
project(bitmanipulation CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(cmake/StandardProjectSettings.cmake) # set the build type (default: 'debug')
include(cmake/CompilerWarnings.cmake)        # set compiler warnings
include(cmake/StaticAnalysis.cmake)          # include static analysis

add_subdirectory(src)

option(ENABLE_TESTING "Enable Test Builds" ON)
if(ENABLE_TESTING)
    enable_testing()
    message(STATUS "Building Tests enabled.")
    add_subdirectory(test)
endif()
