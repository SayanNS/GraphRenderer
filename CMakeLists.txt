cmake_minimum_required(VERSION 3.16.3)
project(Graph)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories(Graph PRIVATE ${SDL2_INCLUDE_DIRS})
add_executable(Graph main.cpp function.cpp parser.cpp scanner.cpp token.cpp)

target_link_libraries(Graph ${SDL2_LIBRARIES})
