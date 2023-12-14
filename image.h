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

typedef struct image_t_prototype image_t;
typedef struct pixel_t_prototype pixel_t;
typedef struct position_t_prototype position_t;

#define MAX_PGM_LINE_SIZE 70

// Image loading states
#define IMAGE_NOT_LOADED 0
#define IMAGE_READ_PGM_TYPE 1
#define IMAGE_LOADING 2

// For RGB images
#define IMAGE_READ_DATA 10
#define IMAGE_READ_DATA_RED 11
#define IMAGE_READ_DATA_GREEN 12
#define IMAGE_READ_DATA_BLUE 13

#define IMAGE_LOADED 100

struct pixel_t_prototype{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct position_t_prototype{
	uint32_t x;
	uint32_t y;
};

struct image_t_prototype{
	/**
	 * (P)1 ASCII black and white
	 * (P)2 ASCII grayscale
	 * (P)3 ASCII color
	 * (P)4 Binary black and white
	 * (P)5 Binary grayscale
	 * (P)6 Binary color
	 */
	int type;

	size_t width;
	size_t height;

	// Don't yet know why this is here
	size_t max_data_value;

	// Actual data
	pixel_t **data;

	// Selection data
	position_t selection_start;
	position_t selection_end;

	// Used for reading the image
	size_t read_x;
	size_t read_y;
	int state;

	// Precessing functions
	void (*load)(image_t *, string_t);
};


// Constructors
image_t new_empty_image();

image_t new_image(FILE *file);

pixel_t new_pixel_mono_color(uint8_t color);

pixel_t new_pixel_color(uint8_t red, uint8_t green, uint8_t blue);

position_t new_position(uint32_t x, uint32_t y);

// Constructor helpers

void image_read_type(image_t *image, string_t buffer);

void image_read_width(image_t *image, string_t buffer);

void image_read_height(image_t *image, string_t buffer);

void image_read_max_value(image_t *image, string_t buffer);

void image_read_mono_data(image_t *image, string_t buffer);

void image_read_rgb_data(image_t *image, string_t buffer);

// Destructor

void free_image_pointer(image_t *image);

void free_image(image_t image);

// Image processing

// Getters
bool is_mono(image_t *image);

bool is_reading_binary(image_t *image);

bool is_binary(image_t *image);

void print_histogram(image_t *image, uint32_t x, uint32_t bins);

// Setters

int set_selection(image_t *image, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);


#endif //TEMA3_IMAGE_H
