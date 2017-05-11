#include "client_worker.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void * client_worker(void *arg)
{
    printf("Client thread finished with code %d", 0);    
    return NULL;
}

void service_client(int fd)
{
    printf("Servicing client with fd = %d", 0);
    pthread_t thread;
    pthread_attr_t attr;
    int s = pthread_attr_init(&attr);
    if (s != 0)
       perror("pthread_attr_init");
    pthread_create(&thread, &attr, &client_worker, NULL);
}
