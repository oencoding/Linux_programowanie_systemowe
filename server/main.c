#include <unistd.h> 
#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "listener.h"
#include "config_reader.h"

int main(int argc, char* argv[])
{
    char * config_file = "server.config";
    if (argc > 1)
        config_file = argv[1];
    SConfiguration configuration = read_configuration(config_file);
    create_listener(&configuration);
}