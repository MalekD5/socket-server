cmake_minimum_required(VERSION 3.29)
project(sockets C)

set(CMAKE_C_STANDARD 11)
link_libraries(ws2_32 wsock32)

add_executable(sockets main.c)
