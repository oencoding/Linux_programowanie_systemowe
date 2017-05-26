#include "client_worker.h"
#include "command_parser.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFFER_SIZE 0x100

static void * client_worker(void *arg)
{
    int fd = *(int*)arg;
    ssize_t nread;
    char buffer[BUFFER_SIZE];
    while((nread = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        char * response = NULL;
        int response_length = 0;
        if (parse_command(buffer, nread, &response, &response_length))
        {
            if (response != NULL)
                write(fd, response, response_length);
        }
    }
    if (close(fd) != 0)
        perror("close error");
    printf("Client thread for %d finished . \n", fd);    
    return NULL;
}

void service_client(int fd)
{
    printf("Servicing client with fd = %d\n", fd);
    pthread_t thread;
    pthread_create(&thread, NULL, &client_worker, (void*)&fd);
}
