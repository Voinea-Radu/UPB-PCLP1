# Copyright 2023 Echipa PCLP1

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = infinite_product codeinvim gigel_and_the_checkboard nomogram

build: $(TARGETS)

infinite_product: infinite_product.c
	$(CC) $(CFLAGS) infinite_product.c math_utils.h math_utils.c -lm -o infinite_product

codeinvim: codeinvim.c
	$(CC) $(CFLAGS) codeinvim.c points_utils.h points_utils.c utils.h utils.c -o codeinvim

gigel_and_the_checkboard: gigel_and_the_checkboard.c
	$(CC) $(CFLAGS) gigel_and_the_checkboard.c board_utils.h board_utils.c utils.h utils.c -o gigel_and_the_checkboard

nomogram: nomogram.c
	$(CC) $(CFLAGS) nomogram.c namogram_utils.h namogram_utils.c utils.h utils.c -o nomogram

pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
