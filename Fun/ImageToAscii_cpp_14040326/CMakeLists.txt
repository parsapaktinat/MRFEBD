cmake_minimum_required(VERSION 3.30)
project(ImageToAscii_cpp_14040326)

set(CMAKE_CXX_STANDARD 20)

add_executable(ImageToAscii_cpp_14040326 main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageToAscii_cpp_14040326 ${OpenCV_LIBS})