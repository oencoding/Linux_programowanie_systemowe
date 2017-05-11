CC=gcc
CFLAGS=-I. -w -lpthread
DEPS = listener.h
OBJ = main.o listener.o client_worker.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)