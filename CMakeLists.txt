cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS  "-Wall -Wextra -Wshadow -W -Ofast -flto")

project(out)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/main.cpp
                    ${CMAKE_SOURCE_DIR}/Node.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
