CC=gcc
CFLAGS=-g -Iinclude
LDFLAGS=-lreadline
OBJS=kernel/kernel.o kernel/system.o kernel/20140653/fork.o

all: minios

minios: $(OBJS)
	$(CC) -o minios $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f minios $(OBJS)

