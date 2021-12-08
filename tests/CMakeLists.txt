add_executable(tests 
    tests.cpp
    ../src/utils.cpp
)

set_target_properties(tests PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

target_link_libraries(tests PUBLIC box2d sfml-graphics sfml-audio sfml-network sfml-system sfml-window)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES tests.cpp)