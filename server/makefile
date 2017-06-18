CC=gcc
CFLAGS=-I. -w -lpthread -lmxml -lconfig -ggdb
DEPS = listener.h commands/command.h
OBJS = main.o listener.o connection_worker.o command_executor.o config_reader.o commands/interface_list.o

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

#
# Clean everything...
#

clean:
	echo Cleaning build files...
	$(RM) $(OBJS)
	$(RM) server
