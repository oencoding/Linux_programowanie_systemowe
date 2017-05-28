#include <stdio.h>

#include "command_executor.h"
#include "../libexpat/expat/lib/expat.h"
#include "dependencies/utlist.h"

CCommandItem *add_command_item(CCommandItem *prev, const char* name)
{
    if (!prev)
        return NULL;
    CCommandItem *new_item = (CCommandItem *)malloc(sizeof(CCommandItem));
    if (!new_item)
        return NULL;
    new_item->next = NULL;
    new_item->name = malloc(strlen(name)+1) ;
    strcpy(new_item->name, name);
    new_item->value = NULL;
    while (prev->next)
        prev = prev->next;
    prev->next = new_item;
    return new_item;
}

void set_command_item_value(CCommandItem *item, const char* value)
{
    if (!item)
        return;
    item->value = malloc(strlen(value)+1);
    strcpy(item->value, value);
}

void destroy_command_items(const CCommandItem *first)
{
    CCommandItem *item = first;
    while (item)
    {
        CCommandItem *next = item->next;
        free(item->name);
        free(item->value);
        free(item);
        item = next;
    }
}


void xml_start(void *data, const char *el, const char **attr)
{
    CCommand *command = (CCommand *)data;
    if (command->xml_parse_level == 0)
    {
        if (strcmp(el, "List") == 0)
            command->type = get_list;
        if (strcmp(el, "Details") == 0)
            command->type = get_details;
    }
    else if (command->xml_parse_level == 1)
    {
        if (command->type == get_details)
        {
            if (strcmp(el, "Interface") == 0)
                command->xml_parse_item = add_command_item(command, el);                
        }
    } 
    else if (command->xml_parse_level == 2)
    {
        if (command->xml_parse_item 
            && strcmp(command->xml_parse_item->name, "Interface") == 0)
            set_command_item_value(command->xml_parse_item, el);
    }

    command->xml_parse_level++;
}


void xml_end(void *data, const char *el)
{
    CCommand *command = (CCommand *)data;
    command->xml_parse_level--;
}



CCommand *parse_command(char* command_string, const int command_length)
{
     CCommand *command = (CCommand *)malloc(sizeof(CCommand));
     command->type   = unknown;
     command->status = unparsed;
     command->params = NULL;
     command->result = NULL;
     command->xml_parse_level  = 0;
     command->xml_parse_item = NULL;
     XML_Parser parser = XML_ParserCreate(NULL);
     XML_SetUserData(parser, command);
     if (parser)
     {
        XML_SetElementHandler(parser, xml_start, xml_end);
        if (XML_Parse(parser, command_string, command_length, true))
            command->status = valid;
            else
            fprintf(stderr, "Parse error at line %d:\n%s\n", XML_GetCurrentLineNumber(parser), XML_ErrorString(XML_GetErrorCode(parser)));
     }
     return command;
}


void execute_command(CCommand * command)
{
    command->status = executed;
}


char *prepare_response(CCommand *command)
{
    char *message;
    switch (command->status)
    {
        case executed:
            message = "Executed";
            break;
        default:
            message = "Failed";
    }
    char *response =(char*) malloc(sizeof(message));
    strcpy(response, message);
    return response;
}

void destroy_command(CCommand *command)
{
    if (!command)
        return;
    destroy_command_items(command->params);
    destroy_command_items(command->result);
    free(command);
}



