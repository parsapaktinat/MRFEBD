cmake_minimum_required(VERSION 3.30)
project(ImageToAscii_cpp_sdl2_14040327)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        /usr/include/SDL2
)

include_directories(
        /usr/lib/x86_64-linux-gnu
)

add_executable(ImageToAscii_cpp_sdl2_14040327 main.cpp)

target_link_libraries(ImageToAscii_cpp_sdl2_14040327
        ${SDL2_LIBRARIES}
        SDL2_image
)
