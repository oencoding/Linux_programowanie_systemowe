#pragma once;
#include "commands/command.h"
#include <stdbool.h>

CCommand *parse_command(char* command_string, const int command_length);
void execute_command(CCommand * command);
char *prepare_response(CCommand *command);
void destroy_command(CCommand *command);
