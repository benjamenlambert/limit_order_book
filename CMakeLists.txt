cmake_minimum_required(VERSION 3.15)
project(limit_order_book)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp)
add_executable(limit_order_book ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(limit_order_book src)

add_subdirectory(tests)