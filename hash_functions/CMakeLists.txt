cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME hash)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if (NOT MSVC)
        add_compile_options(-O0)
    endif()
endif()

if (NOT MSVC)
    add_compile_options(-Wall)
    add_compile_options(-Wextra)
    add_compile_options(-Wimplicit-fallthrough)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-ferror-limit=10)

        add_compile_options(-Weverything)
        add_compile_options(-Wno-c++98-compat)
        add_compile_options(-Wno-c++98-compat-pedantic)
        add_compile_options(-Wno-padded)

        add_compile_options(-Wshorten-64-to-32)
        add_compile_options(-Wextra-semi)
        add_compile_options(-Wzero-as-null-pointer-constant)
        add_compile_options(-Wshadow-uncaptured-local)
        add_compile_options(-Wcovered-switch-default)
        add_compile_options(-Wsign-conversion)
        add_compile_options(-Wcovered-switch-default)
        add_compile_options(-Wshadow)
        add_compile_options(-Wshadow-field)

        #add_compile_options(-fsanitize=memory)
        #add_link_options(-fsanitize=memory)

        #add_compile_options(-fsanitize=undefined)
        #add_link_options(-fsanitize=undefined)

        #add_compile_options(-fsanitize=address)
        #add_link_options(-fsanitize=address)
    else()
    endif()
endif()

# For this project, we're not interested in some things
if (MSVC)
    add_compile_options(-D _CRT_SECURE_NO_WARNINGS)
endif()

if (NOT MSVC)
    add_compile_options(-Wpedantic)
endif()

add_subdirectory(fnv)
add_subdirectory(sip)

add_executable(${PROJECT_NAME}test main.cpp)
target_link_libraries(${PROJECT_NAME}test fnv sip)
