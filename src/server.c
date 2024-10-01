#include "server.h"

char *check_dir_option(int argc, char *argv[])
{
    if (argc == 3)
    {
        if (strcmp(argv[1], "--directory") == 0 && strlen(argv[2]) >= 1)
        {
            printf("Directory with files is : %s\n", argv[2]);

            return argv[2];
        }
    }
    else
    {
        return '\0';
    }
}

char *open_file(char *folder_name, char *file)

{
    char *path = malloc(sizeof(char) * (strlen(folder_name) + strlen(file)));
    char *buffer = (char *)malloc(sizeof(char) * 256);

    memset(buffer, 0, 256);
    memset(path, 0, sizeof(char) * strlen(folder_name));

    strcat(file, ".txt");

    FILE *f = fopen(strcat(strcat(strcat(path, folder_name), "/"), file), "r");

    if (f != NULL)
    {
        fread(buffer, 1, 256, f);
        printf("%s\n", buffer);

        fclose(f);
    }
    else
    {
        printf("Nothing");
        *buffer = '\0';

        return buffer;
    }

    return buffer;
}

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

void *handle_connection(int id_client, char *dir)
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
    if (strncmp(request, "GET /files/", 11) == 0)
    {
        if (*dir != '\0')
        {

            char *ptr = finder("/files/", request);
            if (ptr != NULL)
            {
                ptr = open_file(dir, ptr);
                if (*ptr != '\0')
                {
                    sprintf(response,
                            "HTTP/1.1 200 OK\r\nContent-Type: "
                            "application/octet-stream\r\nContent-Length: %zu\r\n\r\n%s",
                            strlen(ptr), ptr);

                    send(id_client, response, strlen(response), 0);
                }
              
            }
            
        }
       
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