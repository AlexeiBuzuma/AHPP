CC=gcc
CFLAGS=-Wall -std=c99
NOVECT_CFLAGS= $(CFLAGS) -O2
VECT_FLAGS= $(CFLAGS) -O3 -msse2 -ftree-vectorizer-verbose=5 -funsafe-math-optimizations
SOURCES=main.c
EXECUTABLE_NOVECT=novect
EXECUTABLE_VECT=vect
ASM_NOVECT=novect.s
ASM_VECT=vect.s

all: $(SOURCES) $(EXECUTABLE_NOVECT) $(EXECUTABLE_VECT) $(ASM_NOVECT) $(ASM_VECT)

$(ASM_NOVECT): $(SOURCES)
	$(CC) $(SOURCES) $(NOVECT_CFLAGS) -S -o $@

$(EXECUTABLE_NOVECT): $(SOURCES)
	$(CC) $(SOURCES) $(NOVECT_CFLAGS) -o $@

$(ASM_VECT): $(SOURCES)
		$(CC) $(SOURCES) $(VECT_FLAGS) -S -o $@

$(EXECUTABLE_VECT): $(SOURCES)
	$(CC) $(SOURCES) $(VECT_FLAGS) -o $@

clean: $(SOURCES)
	rm $(EXECUTABLE_NOVECT) $(EXECUTABLE_VECT) $(ASM_NOVECT) $(ASM_VECT)

remake: $(SOURCES)
	make clean
	make all
