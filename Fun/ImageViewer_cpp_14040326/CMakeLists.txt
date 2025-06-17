cmake_minimum_required(VERSION 3.30)
project(ImageViewer_cpp_14040326)

set(CMAKE_CXX_STANDARD 20)

add_executable(ImageViewer_cpp_14040326 main.cpp)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS}) # Add SDL2 include directories
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}) # Link SDL2 libraries
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageViewer_cpp_14040326 ${OpenCV_LIBS})