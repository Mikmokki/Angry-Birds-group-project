add_executable(tests 
    tests.cpp
    ../src/utils.cpp
    ../src/converters.cpp
)

set_target_properties(tests PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

target_link_libraries(tests PUBLIC box2d sfml-graphics sfml-audio sfml-network sfml-system sfml-window)