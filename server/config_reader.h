#pragma once

typedef struct SConfiguration
{
    int Port;
    int MaxClients;
} SConfiguration;
 
SConfiguration read_configuration(char * fileName);
