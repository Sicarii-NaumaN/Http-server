cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package( Boost 1.71 REQUIRED COMPONENTS system thread)
include_directories(
        SYSTEM ${Boost_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(server main.cpp utils/config_parser.cpp server/server.cpp http/header.cpp http/header.hpp http/request.cpp http/request.hpp http/response.cpp http/response.hpp http/socket.cpp http/socket.hpp)

target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})