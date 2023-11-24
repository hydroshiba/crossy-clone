if(NOT WIN32)
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchain/windows.cmake CACHE STRING "Windows toolchain file")
endif()

cmake_minimum_required(VERSION 3.20)
project(crossy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE cpp_files ${PROJECT_SOURCE_DIR}/source/*.cpp)
    
include_directories(asset)
include_directories(source/internal)
include_directories(source/object)
include_directories(source/scene)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    file(GLOB_RECURSE resources ${PROJECT_SOURCE_DIR}/asset/*.rc)
endif()

add_executable(${PROJECT_NAME} ${cpp_files} ${resources})

target_link_libraries(${PROJECT_NAME} winmm.lib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
    if(NOT CMAKE_BUILD_TYPE MATCHES "Debug")
        add_compile_options(${PROJECT_NAME} PRIVATE /O2)
    endif()
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Ofast -Wpedantic -fpermissive)
endif()