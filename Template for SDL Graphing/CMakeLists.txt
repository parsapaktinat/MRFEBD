cmake_minimum_required(VERSION 3.30)
project(Template_for_SDL_Graphing)

set(CMAKE_CXX_STANDARD 20)

add_executable(Template_for_SDL_Graphing main.cpp)

# linux of cource
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}) # Add SDL2 include directories
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}) # Link SDL2 libraries

# for windows
#target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
