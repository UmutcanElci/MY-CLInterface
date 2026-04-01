TARGET = bin/cli
IDIR = ./include
CC = gcc
CFLAGS = -I$(IDIR) -Wall
LDLIBS = -lncurses

SRCS = $(shell find src -name "*.c")

OBJS = $(SRCS:src/%.c=obj/%.o)

$(TARGET) : $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

obj/%.o : src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf obj bin
