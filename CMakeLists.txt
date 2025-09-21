cmake_minimum_required(VERSION 3.20)

project(searchserver)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HeaderFiles)
#set(RESOURCES ${CMAKE_SOURCE_DIR}/resources)

add_subdirectory(SourceFiles)
add_subdirectory(Tests)