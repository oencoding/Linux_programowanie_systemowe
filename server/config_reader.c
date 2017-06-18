#include "config_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

SConfiguration read_configuration(char * fileName)
{
    SConfiguration configuration = {DEFAULT_PORT, DEFAULT_MAX_CLIENTS};
    config_t config;
    config_init(&config);
    if (config_read_file(&config, fileName))
    {
        char *file_version = NULL;
        if (CONFIG_TRUE == config_lookup_string(&config, "version", &file_version))
            printf("Reading setting file %s, version %s\n", fileName, file_version);
        config_setting_t *root_setting = config_root_setting(&config);
        if (root_setting != NULL)
        {
            config_setting_t *server_setting = config_setting_get_member(root_setting, "server");
            if (server_setting != NULL)
            {
                config_setting_lookup_int(server_setting, "port", &(configuration.Port));
                config_setting_lookup_int(server_setting, "max_clients", &(configuration.MaxClients));
            }
        }
    }
    config_destroy(&config);
    return configuration;
}