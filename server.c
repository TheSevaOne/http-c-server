#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

#define SO_REUSEPORT 15
int reuse = 1;

void *handle_connection(int id_client);

char *finder(char *to_find, char *request)
{
	char *ptr = strstr(request, to_find);
	if (ptr != NULL)
	{
		ptr += strlen(to_find);
		char *word = ptr;
		while (*word != ' ' && *word != '\0' && *word != '\r' && *word != '\n')
		{
			word++;
		}
		*word = '\0';
	}
	return ptr;
}

int main()
{

	setbuf(stdout, NULL);

	int server_fd, client_addr_len;
	struct sockaddr_in client_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		printf("Socket creation failed: %s...\n", strerror(errno));
		return 1;
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0)
	{
		printf("SO_REUSEPORT failed: %s \n", strerror(errno));
		return 1;
	}

	struct sockaddr_in serv_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(4221),
		.sin_addr = {htonl(INADDR_ANY)},
	};

	if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
	{
		printf("Bind failed: %s \n", strerror(errno));
		return 1;
	}

	int connection_backlog = 5;
	if (listen(server_fd, connection_backlog) != 0)
	{
		printf("Listen failed: %s \n", strerror(errno));
		return 1;
	}

	printf("Waiting for a client to connect...\n");
	client_addr_len = sizeof(client_addr);

	printf("Client connected\n");
	while (1)
	{

		int id_client = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
		handle_connection(id_client);
	}
	close(server_fd);
	return 0;
}

void *handle_connection(int id_client)
{
	const char *message_404 = "HTTP/1.1 404 Not Found\r\n\r\n";
	char *message_200 = "HTTP/1.1 200 OK\r\n\r\n";
	char *response = NULL;
	char *request = NULL;
	request = (char *)malloc(sizeof(char) * 256);

	response = (char *)malloc(sizeof(char) * 256);

	recv(id_client, request, 256, 0);

	if (memcmp(request, "GET / ", 6) == 0)
	{
		send(id_client, message_200, strlen(message_200), 0);
	}

	if (strncmp(request, "GET /user-agent", 15) == 0 )
	{
		char *ptr = finder("User-Agent: ", request);
		sprintf(response,
				"HTTP/1.1 200 OK\r\nContent-Type: "
				"text/plain\r\nContent-Length: %zu\r\n\r\n%s",
				strlen(ptr), ptr);

		send(id_client, response, strlen(response), 0);
	}
	if (strncmp(request, "GET /echo/", 10) == 0)
	{
		char *ptr = finder("/echo/", request);

		sprintf(response,
				"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
				"%ld\r\n\r\n%s",
				strlen(ptr), ptr);

		send(id_client, response, strlen(response), 0);
	}

	else
	{
		send(id_client, message_404, strlen(message_404), 0);
	}

	free(response);
	free(request);
}