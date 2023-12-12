/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_IMAGE_H
#define TEMA3_IMAGE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <bits/types/FILE.h>
#include <stdlib.h>

#include "string_utils.h"

typedef union{
	/**
	 * RED Is stored as bits 0-7
	 * GREEN Is stored as bits 8-15
	 * BLUE Is stored as bits 16-23
	 * Bits 24-31 are unused
	 */
	uint32_t value;
	struct{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	} rgb;
} pixel_t;

typedef struct{
	bool loaded;
	/**
	 * (P)1 ASCII black and white
	 * (P)2 Binary black and white
	 * (P)3 ASCII grayscale
	 * (P)4 Binary grayscale
	 * (P)5 ASCII color
	 * (P)6 Binary color
	 */
	int type;
	size_t width;
	size_t height;
	pixel_t **data;
} image_t;


image_t load_image(FILE *file);

pixel_t new_pixel_mono_color(uint8_t color);

pixel_t new_pixel_color(uint8_t red, uint8_t green, uint8_t blue);

void free_image_pointer(image_t *image);
void free_image(image_t image);

#endif //TEMA3_IMAGE_H
