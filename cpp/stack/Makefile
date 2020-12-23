CC=g++
CFLAGS=-Wall -g -I.

main: stack.o main.o
	$(CC) $(CFLAGS) -o stack stack.o main.o

.PHONY: clean

clean:
	rm -rf stack stack.o main.o

