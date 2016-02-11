CC=gcc
CFLAGS=
VECT_FLAGS=-O3 -ftree-vectorizer-verbose=5 -funsafe-math-optimizations 
SOURCES=main.c
EXECUTABLE_NOVECT=novect
EXECUTABLE_VECT=vect
ASM_NOVECT=novect.s
ASM_VECT=vect.s

all: $(SOURCES) $(EXECUTABLE_NOVECT) $(EXECUTABLE_VECT) $(ASM_NOVECT) $(ASM_VECT)

$(ASM_NOVECT): $(SOURCES)
	$(CC) -O2 $(SOURCES) $(CFLAGS) -S -o $@

$(EXECUTABLE_NOVECT): $(SOURCES)
	$(CC) -O2 $(SOURCES) $(CFLAGS) -o $@

$(ASM_VECT): $(SOURCES)
		$(CC) $(SOURCES) $(VECT_FLAGS) $(CFLAGS) -S -o $@

$(EXECUTABLE_VECT): $(SOURCES)
	$(CC) $(SOURCES) $(VECT_FLAGS) $(CFLAGS) -o $@

clean: $(SOURCES)
	rm $(EXECUTABLE_NOVECT) $(EXECUTABLE_VECT) $(ASM_NOVECT) $(ASM_VECT)

remake: $(SOURCES)
	make clean
	make all
