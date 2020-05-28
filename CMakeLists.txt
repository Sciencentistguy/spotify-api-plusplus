cmake_minimum_required(VERSION 3.17.2)
project(spotify-api-plusplus)

set(CMAKE_CXX_STANDARD 17)

set(SPOTIFY_PLUSPLUS_VERSION 1.0)

find_package(CURL)
set(LIBS ${LIBS} ${CURL_LIBRARIES})
include_directories(${CURL_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)

add_executable(TestEndpoints tests/TestEndpoints.cpp)

target_link_libraries(
        TestEndpoints
        gtest
        gtest_main
        spotify-api-plusplus
        pthread
)

enable_testing()
add_test(TestEndpoints ${PROJECT_BINARY_DIR}/TestEndpoints)
