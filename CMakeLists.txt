cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

set(BOX2D_DIR "${CMAKE_SOURCE_DIR}/libs/box2d")
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML")

option(BUILD_TESTS "Build the tests" ON)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${BOX2D_DIR}")
include_directories (/usr/include/freetype2)
# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project (angry_birds)

file(GLOB SOURCES src/*.cpp)
set(EXECUTABLE_NAME "angry_birds")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Box2D
add_subdirectory("${BOX2D_DIR}" box2d)
target_link_libraries(angry_birds box2d)
SET(BOX2D_BUILD_TESTBED false CACHE BOOL "skip building testbed" FORCE)
SET(BOX2D_BUILD_UNIT_TESTS false CACHE BOOL "skip building unit tests" FORCE)

# SFML
#
#add_subdirectory("${SFML_DIR}" SFML)
#
if(UNIX)
find_package(SFML 2.5 
COMPONENTS 
  system window graphics network audio REQUIRED)
  else(UNIX)
  add_subdirectory("${SFML_DIR}" SFML)
endif(UNIX)



target_link_libraries(angry_birds sfml-graphics sfml-audio sfml-network sfml-system sfml-window)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(WIN32)
    # Copy openal dynamic lib to build folder in order to get sounds working
    file(COPY_FILE libs/SFML/extlibs/bin/x64/openal32.dll "${CMAKE_BINARY_DIR}/openal32.dll")
endif()

target_include_directories(angry_birds PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/libs")
