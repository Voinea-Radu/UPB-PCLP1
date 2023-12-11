# Copyright 2023 Echipa PCLP1

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g3

# define targets
TARGETS = my_octave

build: $(TARGETS)

my_octave: main.c
	$(CC) $(CFLAGS) main.c registry_manager.c registry_manager.h state_manager.c state_manager.h -lm -o my_octave

pack:
	zip -FSr 315CA_VoineaRadu_TEMA3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean