#include <unistd.h> 
#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "listener.h"

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    printf("Listener created with code %d\n", create_listener(1060, 5));
}