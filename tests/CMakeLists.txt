project(runtests)
enable_testing()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wunreachable-code -Wold-style-cast -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wunreachable-code -Wold-style-cast -fprofile-arcs -ftest-coverage")
include(GoogleTest)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES ../src/server.c main.cpp)
set(HEADERS ../src/server.h tests.h)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} gcov)
target_link_libraries(${PROJECT_NAME} gtest gtest_main gmock pthread)
