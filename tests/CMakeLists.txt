project(runtests)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES ../src/server.c main.cpp)
set(HEADERS ../src/server.h tests.h)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
