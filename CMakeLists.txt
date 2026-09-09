
cmake_minimum_required(VERSION 3.15)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lis_lib STATIC 
    "src/find.cpp"
    "src/engine.cpp"
    "src/config.cpp"
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