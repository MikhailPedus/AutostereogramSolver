cmake_minimum_required(VERSION 2.6)
project(stereogramSolver)

find_package(OpenCV REQUIRED)

add_executable(stereogramSolver main.cpp StereogramBuilder.cpp StereogramSolver.cpp)
target_link_libraries(stereogramSolver ${OpenCV_LIBS})
