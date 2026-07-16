cmake_minimum_required(VERSION 3.20)
project(LexAndParseWithCpp LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
target_compile_definitions(project_options INTERFACE unix)
target_compile_options(project_options INTERFACE
    "-include${CMAKE_CURRENT_SOURCE_DIR}/compat.h"
)
target_include_directories(project_options INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Toolbox)
add_subdirectory(Lexis)
add_subdirectory(Gramatika)
add_subdirectory(Loma)
add_subdirectory(Examples)
add_subdirectory(Tests)
