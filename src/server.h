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

static int reuse = 1;
static int connection_backlog = 5;

static char  *message_404 = (char *) "HTTP/1.1 404 Not Found\r\n\r\n";
static char *message_200 = (char *) "HTTP/1.1 200 OK\r\n\r\n";

static char *dir;

void *handle_connection(int id_client, char * dir);
char *finder(char *to_find, char *request);
char *open_file(char *folder_name, char *file);
char *check_dir_option (int argc, char *argv[]);