CC=gcc
CFLAGS=-std=gnu11 -Wall
VECT_FLAGS=-O2 -ftree-vectorize -mavx -ftree-vectorizer-verbose=5
SOURCES=main.c
EXECUTABLE_NOVECT=novect
EXECUTABLE_VECT=vect
ASM_NOVECT=novect.s
ASM_VECT=vect.s

all: $(SOURCES) $(EXECUTABLE_NOVECT) $(EXECUTABLE_VECT) $(ASM_NOVECT) $(ASM_VECT)

$(ASM_NOVECT): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -S -o $@

$(EXECUTABLE_NOVECT): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

$(ASM_VECT): $(SOURCES)
		$(CC) $(SOURCES) $(VECT_FLAGS) $(CFLAGS) -S -o $@

$(EXECUTABLE_VECT): $(SOURCES)
	$(CC) $(SOURCES) $(VECT_FLAGS) $(CFLAGS) -o $@

clean: $(SOURCES)
	rm $(EXECUTABLE_NOVECT) $(EXECUTABLE_VECT) $(ASM_NOVECT) $(ASM_VECT)

remake: $(SOURCES)
	make clean
	make all
