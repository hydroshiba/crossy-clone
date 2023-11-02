cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

project(crossy)

file(GLOB_RECURSE cpp_files
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/game/*.cpp
    ${PROJECT_SOURCE_DIR}/object/*.cpp)

include_directories(asset)
include_directories(game)
include_directories(object)

add_executable(${PROJECT_NAME} ${cpp_files})

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -Wpedantic)
endif()