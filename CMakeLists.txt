cmake_minimum_required (VERSION 3.22.0)

get_filename_component(PROJECT_FOLDER_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_FOLDER_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/HeaderFiles/)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/SourceFiles/) 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "" FORCE)
endif()

add_subdirectory(nlohmann_json)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce8.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(${PROJECT_NAME}
    ${MY_SRC_DIR}/main.cpp
    ${MY_SRC_DIR}/converterjson.cpp
    ${MY_SRC_DIR}/invertedindex.cpp
    ${MY_SRC_DIR}/searchserver.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

add_executable(tests
    Tests/tests.cpp
    ${MY_SRC_DIR}/converterjson.cpp
    ${MY_SRC_DIR}/invertedindex.cpp
    ${MY_SRC_DIR}/searchserver.cpp
)

target_include_directories(tests PRIVATE ${MY_INCLUDE_DIR})

target_link_libraries(tests PRIVATE
    gtest_main
    nlohmann_json::nlohmann_json
)

# Àâòîìàòè÷åñêîå äîáàâëåíèå òåñòà äëÿ CTest
add_test(NAME AllTests COMMAND tests)
