#include <unistd.h> 
#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "listener.h"

int main(int argc, char* argv[])
{
    create_listener(1060);
}