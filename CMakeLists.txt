cmake_minimum_required(VERSION 3.10)
project(toySTL)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(test_Vector test/test_Vector.cc)
target_sources(test_Vector PRIVATE src/Vector.cc)