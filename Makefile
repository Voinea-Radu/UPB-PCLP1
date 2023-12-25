# Copyright 2023 Echipa PCLP1

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g3

# define targets
TARGETS = image_editor

build: $(TARGETS)

image_editor: main.c
	$(CC) $(CFLAGS) main.c state_manager.c state_manager.h string_utils.c string_utils.h image.c image.h utils.c utils.h instructions.h instructions.c -lm -o image_editor

pack:
	zip -FSr 315CA_VoineaRadu_TEMA3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean