#include "connection_worker.h"
#include "command_executor.h"
#include "commands/command.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFFER_SIZE 0x100

void * client_worker(void *arg)
{
    int fd = (int)arg;
    ssize_t nread; 
    char buffer[BUFFER_SIZE];
    while((nread = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        CCommand* c = parse_command(buffer, nread);
        {
            if (c)
            {
                if (c->status == valid)
                    execute_command(c);
                char *response = prepare_response(c);
                if (response)
                {
                    write(fd, response, sizeof(response));
                    free(response);
                }
            destroy_command(c);
            }
        }
    }
    if (close(fd) != 0)
    {
        perror("close error");
    }
    printf("Client thread for %d finished . \n", fd);    
    return NULL;
}

void service_client(int fd)
{
    printf("Servicing client with fd = %d\n", fd);
    pthread_t thread;
    pthread_create(&thread, NULL, &client_worker, fd);
}
