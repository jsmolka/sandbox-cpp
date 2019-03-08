cmake_minimum_required(VERSION 2.8)

project(snake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

include(FindSDL2 REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    src/const.h
    src/grid.h
    src/grid.c
    src/key.h
    src/main.c
    src/point.h
    src/point.c
    src/snake.h
    src/snake.c
    src/util.h
    src/vector.h
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
