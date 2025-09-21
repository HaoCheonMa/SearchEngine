cmake_minimum_required(VERSION 3.8)

project(servertest)

# get GTest and JSON from github
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(json)

enable_testing()

add_executable(servertest indextests.cpp servertests.cpp
        ${CMAKE_SOURCE_DIR}/SourceFiles/invertedindex.cpp
        ${CMAKE_SOURCE_DIR}/SourceFiles/searchserver.cpp
        ${CMAKE_SOURCE_DIR}/SourceFiles/converterjson.cpp)

target_include_directories(servertest PUBLIC ${gtest_SOURCE_DIR}/HeaderFiles ${INCLUDE_DIR})

target_link_libraries(servertest PRIVATE gtest_main nlohmann_json::nlohmann_json)