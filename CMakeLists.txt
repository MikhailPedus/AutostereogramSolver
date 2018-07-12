cmake_minimum_required(VERSION 2.6)

if (CMAKE_VERSION VERSION_LESS "3.1")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	endif ()
else ()
	set (CMAKE_CXX_STANDARD 11)
endif ()

project(stereogramBuilder)
project(stereogramSolver)

find_package(Threads)
find_package(OpenCV REQUIRED)

add_executable(stereogramBuilder src/mainBuilder.cpp src/StereogramBuilder.cpp)
add_executable(stereogramSolver src/mainSolver.cpp src/StereogramSolver.cpp)

target_link_libraries(stereogramBuilder ${OpenCV_LIBS})
target_link_libraries(stereogramSolver ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

