# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=gnu11 -g

# Source files and object files
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = a.out

# # Print debugging information
# $(info Source files: $(SRCS))
# $(info Object files: $(OBJS))

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm $(OBJS) $(TARGET)

# all:
# 	gcc -o Nash main.c log.c pi.c hop.c reveal.c proclore.c seek.c bgfg.c task1.c