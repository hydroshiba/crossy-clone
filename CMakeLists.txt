cmake_minimum_required(VERSION 3.20)
project(crossy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE cpp_files
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/game/*.cpp
    ${PROJECT_SOURCE_DIR}/object/*.cpp)

include_directories(asset)
include_directories(game)
include_directories(object)

add_executable(${PROJECT_NAME} ${cpp_files})
target_link_libraries(${PROJECT_NAME} winmm.lib)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX /O2)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -Wpedantic)
endif()