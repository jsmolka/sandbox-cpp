cmake_minimum_required(VERSION 2.8)

project(chip8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(FindSDL2 REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    src/chip8.hpp
    src/chip8.cpp
    src/main.cpp
    src/sdlwindow.hpp
    src/sdlwindow.cpp
    src/types.hpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
