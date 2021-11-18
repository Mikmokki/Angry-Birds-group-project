cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

set(BOX2D_DIR "${CMAKE_SOURCE_DIR}/libs/Box2D")
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${BOX2D_DIR}")

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project (angry_birds)

set(EXECUTABLE_NAME "angry_birds")
add_executable(${EXECUTABLE_NAME} ./src/main.cpp)

# Box2D
add_subdirectory("${BOX2D_DIR}" Box2D)
target_link_libraries(angry_birds box2d)
SET(BOX2D_BUILD_TESTBED OFF CACHE BOOL "skip building testbed" FORCE)
SET(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "skip building unit tests" FORCE)

# SFML
add_subdirectory("${SFML_DIR}" SFML)
target_link_libraries(angry_birds sfml-graphics sfml-audio sfml-network sfml-system sfml-window)

target_include_directories(angry_birds PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/libs")
