set(CMAKE_VERBOSE_MAKEFILE 1)

add_compile_options(-g -Wall)

add_executable(testcpp main.cpp)

target_link_libraries(testcpp pthread)