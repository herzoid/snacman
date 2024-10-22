cmake_minimum_required(VERSION 3.5)

project(sdltest)

set(SDL2_STATIC ON)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/canvas.cpp
    src/canvas.hpp
    src/entity.cpp
    src/entity.hpp
    src/math.cpp
    src/math.hpp
    src/utils.hpp
    )

find_package(SDL2 REQUIRED)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)

#find_library(SDL_LIB SDL2)

#target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf SDL2_gfx)
#target_include_directories($(PROJECT_NAME) PRIVATE $(CMAKE_CURRENT_SOURCE_DIR)/include)

