cmake_minimum_required(VERSION 3.30)
project(SDL_Exercise)

set(CMAKE_CXX_STANDARD 20)

add_executable(SDL_Exercise main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}) # Add SDL2 include directories
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}) # Link SDL2 libraries