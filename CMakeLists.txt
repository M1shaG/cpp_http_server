cmake_minimum_required(VERSION 3.10)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
project(simple_http_server)
add_executable(simple_http_server src/https_tcpServer_linux.cpp src/server_linux.cpp)
