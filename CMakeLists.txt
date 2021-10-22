set(CMAKE_VERBOSE_MAKEFILE 1)

# include(FetchContent)
# FetchContent_Declare(json
#     GIT_REPOSITORY https://github.com/nlohmann/json.git
#     GIT_TAG        v3.9.1
# )
# FetchContent_Declare(fmt
#     GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#     GIT_TAG        master
# )
# FetchContent_MakeAvailable(json fmt)

set(JSON_PATH libs/json/json)
set(FMT_PATH libs/fmt/fmt)

add_compile_options(-g -Wall)

add_executable(testcpp main.cpp sha1.cpp sha1v2.cpp)

target_include_directories(testcpp
    PRIVATE
    ${JSON_PATH}/include
    ${FMT_PATH}/include
)

target_link_directories(testcpp
    PRIVATE
    ${FMT_PATH}/build
)

target_link_libraries(testcpp pthread fmt)