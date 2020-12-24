CC=g++
CFLAGS=-Wall -g -I.

main: array_stack.o list_stack.o main.o
	$(CC) $(CFLAGS) -o stack array_stack.o list_stack.o main.o

.PHONY: clean

clean:
	rm -rf stack stack.o array_stack.o list_stack.o main.o

