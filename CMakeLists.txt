
cmake_minimum_required(VERSION 3.15)

project(MyProject VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(lis_lib STATIC 
    "src/engine.cpp"
    "src/task.cpp"
)


target_include_directories(lis_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(
    lis_lib
    PUBLIC
)

add_executable(lis main.cpp)

target_link_libraries(
    lis 
    PRIVATE 
    lis_lib     
)

enable_testing()

FetchContent_Declare(
    Catch2
    URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.3.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests
    src/tests/test_engine.cpp)
target_link_libraries(unit_tests PRIVATE lis_lib Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(unit_tests)
