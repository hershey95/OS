CC=gcc
CFLAGS=-g -Iinclude -Wall
LDFLAGS=-lreadline
SRCS=$(wildcard kernel/*.c kernel/20140653/*.c)
OBJS=$(SRCS:.c=.o)

# 최종 실행 파일
TARGET=minios

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f minios $(OBJS)

