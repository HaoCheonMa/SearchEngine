cmake_minimum_required(VERSION 3.8)

# get JSON from github
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

#configure_file(${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_CURRENT_BINARY_DIR})
#configure_file(${CMAKE_SOURCE_DIR}/config/requests.json ${CMAKE_CURRENT_BINARY_DIR})

add_executable(searchserver main.cpp converterjson.cpp invertedindex.cpp searchserver.cpp searchengine.cpp)

target_include_directories(searchserver PUBLIC ${INCLUDE_DIR})

target_link_libraries(searchserver PRIVATE nlohmann_json::nlohmann_json)