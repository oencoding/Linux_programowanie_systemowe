#pragma once;

#define EXIT_SUCCESS  0
#define EXIT_SOCEKT_NOT_CREATED  1
#define EXIT_CANNOT_BIND 2
#define EXIT_CANNOT_LISTEN 3
#define EXIT_CANNOT_CONFIGURE 4

int create_listener(int port, int max_clients);