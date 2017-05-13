CC=gcc
CFLAGS=-I. -w -lpthread -ggdb
DEPS = listener.h
OBJS = main.o listener.o client_worker.o command_parser.o

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

#
# Clean everything...
#

clean:
	echo Cleaning build files...
	$(RM) $(OBJS)
	$(RM) server
