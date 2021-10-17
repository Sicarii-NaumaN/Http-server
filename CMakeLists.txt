cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

find_package( Boost 1.6 REQUIRED COMPONENTS system thread)
include_directories(
        SYSTEM ${Boost_INCLUDE_DIR}
)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
include_directories(server/ response/ request/ http/)
add_executable(server main.cpp utils/config_parser.cpp server/server.cpp  http/http.cpp request/request.cpp http/http.cpp response/response.cpp server/transport.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})