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
#include <asm-generic/types.h>

#include "string_utils.h"

// Filters
static const double EDGE_FILTER_FACTOR = 1;
static const __s8 EDGE_FILTER[3][3] = {
		{-1, -1, -1},
		{-1, 8,  -1},
		{-1, -1, -1}
};

static const double SHARPEN_FILTER_FACTOR = 1;
static const __s8 SHARPEN_FILTER[3][3] = {
		{0,  -1, 0},
		{-1, 5,  -1},
		{0,  -1, 0}
};

static const double BLUR_FILTER_FACTOR = 1.0 / 9.0;
static const __s8 BLUR_FILTER[3][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
};

static const double GAUSSIAN_BLUR_FILTER_FACTOR = 1.0 / 16.0;
static const __s8 GAUSSIAN_BLUR_FILTER[3][3] = {
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1}
};

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

struct pixel_t_prototype {
	__s8 red;
	__s8 green;
	__s8 blue;
};

struct position_t_prototype {
	__u32 x;
	__u32 y;
};

struct image_t_prototype {
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

	// TODO Maybe remove at some point
	// Don't yet know why this is here
	// size_t max_data_value;

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
	void (*load)(image_t *image, string_t buffer);
};

// Constructors
image_t new_empty_image(void);

image_t new_image(FILE *file);

pixel_t new_pixel_mono_color(__s8 color);

pixel_t new_pixel_color(__s8 red, __s8 green, __s8 blue);

position_t new_position(__u32 x, __u32 y);

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

void free_data(pixel_t ***data, __u32 size_y);

// Image processing

// Getters
bool is_mono(image_t *image);

bool is_reading_binary(image_t *image);

bool is_binary(image_t *image);

void print_histogram(image_t *image, __u32 x, __u32 bins);

// Setters

int set_selection(image_t *image, __u32 *x1, __u32 *y1, __u32 *x2,
				  __u32 *y2);

void equalize(image_t *image);

// Utils

__u32 *generate_histogram(image_t *image);

__u32 *
generate_histogram_coords(image_t *image, __u32 start_x, __u32 start_y,
						  __u32 end_x, __u32 end_y);

void save_image_ascii(image_t *image, FILE *file);

void save_image_binary(image_t *image, FILE *file);

void rotate(image_t *image, __s16 degrees);

void rotate_sub_matrix(image_t *image, __s16 degrees, __u32 size_x,
					   __u32 size_y, __s8 iterations);

void
rotate_matrix(image_t *image, __s16 degrees, __u32 size_x, __u32 size_y,
			  __s8 iterations);

void crop(image_t *image);

bool apply_filter(image_t *image, __s8 filter[3][3], double factor);

void init_image_data(pixel_t ***data_pointer, __u32 size_x, __u32 size_y);

#endif //TEMA3_IMAGE_H
