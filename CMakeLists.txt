cmake_minimum_required(VERSION 3.20)
project(crossy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE cpp_files
    ${PROJECT_SOURCE_DIR}/source/*.cpp)
    
include_directories(source/game)
include_directories(source/object)
include_directories(source/scene)

add_executable(${PROJECT_NAME} ${cpp_files})
target_link_libraries(${PROJECT_NAME} winmm.lib)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX /O2)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -Wpedantic)
endif()