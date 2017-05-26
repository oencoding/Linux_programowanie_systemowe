CC=gcc
CFLAGS=-I. -w -lpthread -I/usr/include/libxml2 -lxml2 -ggdb
DEPS = listener.h
OBJ = main.o listener.o client_worker.o command_parser.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)