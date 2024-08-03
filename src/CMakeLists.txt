project(server)
set(SOURCES server.c main.c)
set(HEADERS server.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})



