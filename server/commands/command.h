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

typedef struct CCommandItem {
    char *name;
    char *value;
    struct CCommandItem *next;
} CCommandItem;


typedef struct CCommand{
    enum CCommandType   type;
    enum CComandStatus  status;
    CCommandItem        *params;
    CCommandItem        *result;
    // internal xml-parsing fields
    int                 xml_parse_level; 
    CCommandItem        *xml_parse_item; 
} CCommand;
