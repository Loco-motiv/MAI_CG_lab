cmake_minimum_required(VERSION 3.16)
project(Lab1)

# Указание стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Поиск пакета SFML
set(SFML_DIR "C:/libs/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

file(GLOB SOURCES ./*cpp ./*h)

# Добавление исполняемого файла
add_executable(Lab1 ${SOURCES})

# Связывание с библиотеками
target_link_libraries(Lab1 sfml-window opengl32) 