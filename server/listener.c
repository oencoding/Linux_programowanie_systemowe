#pragma once
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include "listener.h"
#include "connection_worker.h"


int create_listener(int port)
{
    struct sockaddr_in server_addr;
    socklen_t sockaddr_in_size = sizeof(struct sockaddr_in);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1){
		perror("Socket create error");
		return EXIT_SOCEKT_NOT_CREATED;
	}
	memset(&server_addr, 0, sockaddr_in_size);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	if (setsockopt(server_fd, SOL_SOCKET,  SO_REUSEADDR, &(int){1}, sizeof(int)) < 0 )
	{
		perror("setsockopt  error");
		return EXIT_CANNOT_CONFIGURE;
	}

	if (bind(server_fd, (struct sockaddr*)&server_addr, sockaddr_in_size)<0)
	{
		perror("bind error");
		return EXIT_CANNOT_BIND;
	}

	if (listen(server_fd, MAX_CLIENTS) < 0)
	{
		perror("listen error");
	 	return EXIT_CANNOT_LISTEN;
	}
	while (1)
	{
		struct sockaddr_in client_addr;
		memset(&client_addr, 0, sockaddr_in_size);
		client_addr.sin_family = AF_INET;
		int client_addr_len = sizeof(client_addr);
		printf("Waiting for next client\n");
		int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
		printf("Client accepted with fd = %d\n", client_fd);
		if (client_fd > 0)
		{
			service_client(client_fd);
		}
		else
		{
			perror("Client accept error");
		}
	}

	close(server_fd);
}
