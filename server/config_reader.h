#pragma once

#define DEFAULT_PORT 1060
#define DEFAULT_MAX_CLIENTS 5

typedef struct SConfiguration
{
    int Port;
    int MaxClients;
} SConfiguration;
 
SConfiguration read_configuration(char * fileName);
