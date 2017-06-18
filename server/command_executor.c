#include <stdio.h>
#include <mxml.h>
#include "command_executor.h"

CCommandElement *add_command_element(CCommandElement *prev, const char* name)
{
	if (!prev)
		return NULL;
	CCommandElement *new_item = (CCommandElement *)malloc(sizeof(CCommandElement));
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

void set_command_element_value(CCommandElement *item, const char* value)
{
	if (!item)
		return;
	item->value = malloc(strlen(value)+1);
	strcpy(item->value, value);
}

 void destroy_command_elements(const CCommandElement *first)
{
	CCommandElement *item = first;
	while (item)
	{
		CCommandElement *next = item->next;
		free(item->name);
		free(item->value);
		free(item);
		item = next;
	}
}

CCommand *parse_command(char* command_string, const int command_length)
{
	 CCommand *command = (CCommand *)malloc(sizeof(CCommand));
	 command->type   = unknown;
	 command->status = unparsed;
	 command->params = NULL;
	 command->result = NULL;
	 mxml_node_t *tree = mxmlLoadString(NULL, command_string, MXML_NO_CALLBACK);
	 if (tree)
	 {
		 mxml_node_t * rootNode = mxmlGetFirstChild(tree);
		 if (rootNode)
		 {
			mxml_node_t * commandNode = mxmlGetNextSibling(rootNode);
			if (commandNode)
			{
				if (0 == strcmp(mxmlGetElement(commandNode), "List"))
				{
					command->type = get_list;
		  			command->status = valid;
				}
				if (0 == strcmp(mxmlGetElement(commandNode), "Interface"))
				{
					command->type = get_details;
		  			command->status = valid;
					mxml_node_t * interfaceNode = mxmlGetFirstChild(commandNode);
					while (interfaceNode)
					{
						if (0 == strcmp(mxmlGetElement(interfaceNode), "MAC"))
						{
							CCommandElement * command_element = add_command_element(command, "MAC");
							int precedes_whitespace;
							char * command_value = mxmlGetText(interfaceNode, &precedes_whitespace);
							if (command_value)
								set_command_element_value(command_element, command_value);
						}
						interfaceNode = mxmlGetNextSibling(interfaceNode);
					}
				}
			}  
		 }

		  mxmlDelete(tree);
	 }
	 return command;
}


void execute_command(CCommand * command)
{
	switch(command->type)
	{
		case get_list:
			get_interface_list(command);
		break;
		default:
			return;
	}
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
	destroy_command_elements(command->params);
	destroy_command_elements(command->result);
	free(command);
}



