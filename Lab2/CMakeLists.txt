cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "C:/libs/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
set(glm_DIR "C:/libs/glm")

file(GLOB_RECURSE SOURCES src/*.cpp glad/*.c)

project(Lab2)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)
find_package(glm CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -O3")
add_executable(Lab2 ${SOURCES})

target_include_directories(Lab2 PUBLIC include glad/include)
target_link_libraries(Lab2 sfml-window opengl32 glm::glm) 