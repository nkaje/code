CC=g++
CFLAGS=-I. -Wall -Werror
DEPS = logger.h
OBJ = logger.o
LIBOUT = logger.so

%.o: %.c $(DEPS)
	$(CC) -c -fpic -o $@ $< $(CFLAGS)

logger: $(OBJ)
	$(CC) -shared -o $(LIBOUT) $^ $(CFLAGS)
