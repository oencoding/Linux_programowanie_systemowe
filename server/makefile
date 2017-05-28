CC=gcc
CFLAGS=-I. -w -lpthread -lexpat -L../libexpat/expat/build -ggdb
DEPS = listener.h commands/command.h
OBJS = main.o listener.o connection_worker.o command_executor.o commands/interface_list.o

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
