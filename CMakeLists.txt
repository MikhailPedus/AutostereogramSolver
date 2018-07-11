cmake_minimum_required(VERSION 2.6)

project(stereogramBuilder)
project(stereogramSolver)

find_package(OpenCV REQUIRED)

add_executable(stereogramBuilder src/mainBuilder.cpp src/StereogramBuilder.cpp)
add_executable(stereogramSolver src/mainSolver.cpp src/StereogramSolver.cpp)

target_link_libraries(stereogramBuilder ${OpenCV_LIBS})
target_link_libraries(stereogramSolver ${OpenCV_LIBS})

