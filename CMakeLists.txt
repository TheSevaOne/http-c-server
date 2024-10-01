cmake_minimum_required(VERSION 3.28)
project(runtests)
include(GoogleTest)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS  " ${CMAKE_C_FLAGS} --coverage")
set(SOURCES ./src/server.c ./tests/main.cpp)
set(HEADERS ./src/server.h ./tests/tests.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}  gcov gtest gtest_main gmock pthread)

project(server)
set(SOURCES ./src/server.c ./src/main.c)
set(HEADERS ./src/server.h)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

