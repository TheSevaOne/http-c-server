#include "server.h"

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

void *handle_connection(int id_client)
{

    char *response = NULL;
    char *request = NULL;
    
    request = (char *)malloc(sizeof(char) * 256);

    response = (char *)malloc(sizeof(char) * 256);

    recv(id_client, request, 256, 0);

    if (memcmp(request, "GET / ", 6) == 0)
    {
        send(id_client, message_200, strlen(message_200), 0);
    }

    if (strncmp(request, "GET /user-agent", 15) == 0)
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