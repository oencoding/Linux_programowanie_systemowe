#pragma once

static enum parse_element{
	none,
	interface
};

enum CCommandType{
	unknown,
	get_list,
	get_details,
	set_mac,
	set_ip
};

enum CComandStatus{
	unparsed,
	valid,
	invalid,
	executed,
	failed
};

typedef struct CCommandElement {
	char *name;
	char *value;
	struct CCommandElement *next;
} CCommandElement;


typedef struct CCommand{
	enum CCommandType   type;
	enum CComandStatus  status;
	CCommandElement     *params;
	CCommandElement     *result;
} CCommand;
