# Compiler settings
CC = gcc
CFLAGS = -Wall -g

# Sources and output
TARGET = bank
SRCS = bank.c 
OBJS = $(SRCS:.c=.o)


# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CLFAG) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean up build files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)