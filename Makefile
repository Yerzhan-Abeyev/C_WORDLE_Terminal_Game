# Set CC to gcc to use gcc as our C compiler
CC = gcc

# Compilation options:
# -g: include debugging info symbols
# -Wall: enable all warnings
CFLAGS = -g -Wall 

# Linking options:
LDFLAGS = 

# List the libraries you need to link with in LDLIBS.
# For example, use -lm for the math library.
LDLIBS = 

.PHONY: default
default: wordle_play

wordle_play: wordle_play.o hashmap.o

wordle_play.o: wordle_play.c hashmap.h

hashmap.o: hashmap.c hashmap.h

.PHONY: clean
clean:
	rm -f *.o *.a a.out core wordle_play

.PHONY: all
all: clean wordle_play


