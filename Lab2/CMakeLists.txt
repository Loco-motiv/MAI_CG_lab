cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "C:/libs/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp glad/*.c)

project(Lab2)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -O3")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include glad/include)
target_link_libraries(${PROJECT_NAME} sfml-window opengl32) 