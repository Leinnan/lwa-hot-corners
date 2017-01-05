#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.6)

set( PROJECT_NAME "X11HotCorner" )
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")


set(SOURCE_FILES src/main.cpp src/Manager.cpp src/Manager.h src/Corner.cpp src/Corner.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
