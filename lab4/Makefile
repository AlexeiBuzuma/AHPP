CC = gcc
CFLAGS = -g -Wall -std=c11 -pedantic -c

all: array

array: array_investigetor.c
	$(CC) -shared -Wl,-soname,array -o array.so -fPIC $<

clean:
	rm -rf *.o *.out *.so *.log