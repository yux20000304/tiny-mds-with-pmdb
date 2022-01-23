cmake_minimum_required(VERSION 3.0)

project(tiny_metadata_server)

set(CMAKE_CXX_FLAGS "-std=c++11")

INCLUDE_DIRECTORIES(include)

set(src src)

add_library(socket src/socket.cpp src/tools.cpp)

add_library(filesystem src/file_system.cpp src/metadata_server.cpp src/tools.cpp)

add_executable(client src/client.cpp include/tools.h)

add_executable(server src/server.cpp include/tools.h)

target_link_libraries(client socket)

target_link_libraries(server filesystem socket)


