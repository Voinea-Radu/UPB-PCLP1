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

// Image loading states
#define IMAGE_NOT_LOADED 0

#define IMAGE_READ_PGM_TYPE 1

#define IMAGE_READ_WIDTH 2
#define IMAGE_READ_HEIGHT 3
#define IMAGE_READ_DATA 4
#define IMAGE_READ_MAX_VALUE 5

// For RGB images
#define IMAGE_READ_DATA_RED 11
#define IMAGE_READ_DATA_GREEN 12
#define IMAGE_READ_DATA_BLUE 13

#define IMAGE_LOADED 100

typedef struct{
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

	size_t max_data_value;

	pixel_t **data;

	// Used for reading the image
	size_t read_x;
	size_t read_y;
	int state;
	int sub_state;
} image_t;

image_t new_image();

image_t load_image(FILE *file);

pixel_t new_pixel_mono_color(uint8_t color);

pixel_t new_pixel_color(uint8_t red, uint8_t green, uint8_t blue);

void free_image_pointer(image_t *image);

void free_image(image_t image);

void read_one_value_ascii_image(image_t *image, string_t *buffer);

void read_rgb_ascii_image(image_t *image, string_t *buffer, size_t *buffer_size);

void init_image_data(image_t *image);

#endif //TEMA3_IMAGE_H
