#include "command_parser.h"
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int parse_command(char* command, int length, char** response, int* response_length)
{
    xmlDocPtr doc; /* the resulting document tree */

    doc = xmlReadMemory(command, length, "command.xml", NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse document\n");
	return FALSE;
    }
    xmlMemoryDump();
    xmlFreeDoc(doc);
    printf("Parsing: %s", command);
    char* res = "Odpowiedź";
    *response_length = strlen(res)+1;
    *response = (char*)malloc(*response_length);
    strcpy(*response, res);
    return TRUE;
}