#define PORT 4221
#define SO_REUSEPORT 15

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>



void *handle_connection(int id_client);
char *finder(char *to_find, char *request);
