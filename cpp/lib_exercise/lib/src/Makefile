CC=g++
CFLAGS=-I. -Wall -Werror
DEPS = %.h
OBJ = logger.o
LIBOUT = liblogger.so

%.o: %.cc $(DEPS)
	$(CC) -c -fpic -o $@ $< $(CFLAGS)

logger: $(OBJ)
	$(CC) -shared -o $(LIBOUT) $^ $(CFLAGS)

clean:
	rm -rf *.so *.o
