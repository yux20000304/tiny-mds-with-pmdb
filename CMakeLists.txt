cmake_minimum_required(VERSION 3.0)

project(tiny_metadata_server)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(LIBPMEMOBJ_CPP_REQUIRED_VERSION 1.9)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPMEMKV REQUIRED libpmemkv)
pkg_check_modules(LIBPMEMOBJ++ REQUIRED libpmemobj++>=${LIBPMEMOBJ_CPP_REQUIRED_VERSION})

include_directories(${LIBPMEMKV_INCLUDE_DIRS})
link_directories(${LIBPMEMKV_LIBRARY_DIRS})

include_directories(include)

set(src src)

add_library(socket src/socket.cpp src/tools.cpp)

add_library(filesystem src/file_system.cpp src/metadata_server.cpp src/tools.cpp src/metadata_system.cpp)

add_executable(client src/client.cpp include/tools.h include/metadata_node.h include/metadata_system.h)

add_executable(server src/server.cpp include/tools.h)

target_link_libraries(client socket ${LIBPMEMKV_LIBRARIES} pthread)

target_link_libraries(server filesystem socket ${LIBPMEMKV_LIBRARIES} pthread)





