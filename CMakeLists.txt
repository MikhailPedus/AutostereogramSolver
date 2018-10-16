cmake_minimum_required(VERSION 2.6)

if (CMAKE_VERSION VERSION_LESS "3.1")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	endif ()
else ()
	set (CMAKE_CXX_STANDARD 11)
endif ()

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

project(stereogramBuilder)
project(stereogramSolver)
project(pointsCloudDisplayer)
project(stereogramTest)

find_package(Threads)
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

#application for building stereogram
add_executable(stereogramBuilder src/mainBuilder.cpp src/StereogramBuilder.cpp)
target_link_libraries(stereogramBuilder ${OpenCV_LIBS})

#application for soving stereogram
add_executable(stereogramSolver src/mainSolver.cpp src/StereogramSolver.cpp)
target_link_libraries(stereogramSolver ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})

#application for display points cloud in *.ply format in 3d view using vtk library (opencv::viz module)
add_executable(pointsCloudDisplayer src/mainDisplayer.cpp)
target_link_libraries(pointsCloudDisplayer ${OpenCV_LIBS})

#tests for stereogram builder/solver
add_executable(stereogramTest src/StereogramSolver.cpp src/StereogramBuilder.cpp src/StereogramTest.cpp)
target_link_libraries(stereogramTest ${OpenCV_LIBS} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
include_directories(stereogramTest ${GTEST_INCLUDE_DIR})
