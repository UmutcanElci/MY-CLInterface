TARGET = bin/cli
IDIR = ./include
CC = gcc
CFLAGS = -I$(IDIR)
LDLIBS = -lncurses

SRCS = $(wildcard src/*.c) $(wildcard src/logger/*.c)

OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

$(TARGET) : $(OBJS)
			@mkdir -p $(@D)
			$(CC) $^ -o $@ $(CFLAGS) $(LDLIBS)

obj/%.o : src/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
			rm -f $(OBJS) $(TARGET)
			rm -rf obj bin
