/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include "image.h"
#include "utils.h"
#include <math.h>

image_t new_image(FILE *file)
{
	bool is_comment = false;

	string_t buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
	size_t buffer_size = 0;

	reset_buffer(buffer, &buffer_size);

	image_t image = new_empty_image();

	image.state = IMAGE_READ_PGM_TYPE;
	image.load = image_read_type;

	char data;
	while (1) {
		data = (char)fgetc(file);

		if (data == '#') {
			is_comment = true;
		}

		if (data == '\n') {
			if (is_comment) {
				is_comment = false;
				continue;
			}
			is_comment = false;
		}

		if (is_comment) {
			continue;
		}

		// Binary file format
		if (is_reading_binary(&image)) {
			buffer[buffer_size++] = data;
			buffer[buffer_size] = '\0';

			image.load(&image, buffer);
			reset_buffer(buffer, &buffer_size);
		} else {
			// ASCII file format
			if (data == '\n' || data == ' ') {
				if (buffer_size == 0) {
					continue;
				}

				image.load(&image, buffer);
				reset_buffer(buffer, &buffer_size);
			} else {
				buffer[buffer_size++] = data;
				buffer[buffer_size] = '\0';
			}
		}

		if (image.state == IMAGE_LOADED) {
			break;
		}
	}

	free(buffer);
	return image;
}

void image_read_type(image_t *image, string_t buffer)
{
	image->type = buffer[1] - '0';

	image->state = IMAGE_LOADING;
	image->load = image_read_width;
}

void image_read_width(image_t *image, string_t buffer)
{
	image->width = strtol(buffer, NULL, 10);

	image->load = image_read_height;
}

void image_read_height(image_t *image, string_t buffer)
{
	image->height = strtol(buffer, NULL, 10);

	// Create the data matrix
	image->data = malloc(image->height * sizeof(pixel_t *));
	for (size_t i = 0; i < image->height; i++) {
		image->data[i] = malloc(image->width * sizeof(pixel_t));
		for (size_t j = 0; j < image->width; j++) {
			image->data[i][j] = new_pixel_color(0, 0, 0);
		}
	}

	// Set the selection to the full image
	set_selection(image, 0, 0, image->width, image->height);

	image->load = image_read_max_value;
}

void image_read_max_value(image_t *image, string_t buffer)
{
	image->state = IMAGE_READ_DATA;

	if (image->type == 1 || image->type == 4) {
		// TODO Maybe remove at some point
		// image->max_data_value = 1;
		if (is_mono(image)) {
			image_read_mono_data(image, buffer);
		}
		return;
	}

	// TODO Maybe Remove at some point
	// image->max_data_value = strtol(buffer, NULL, 10);

	// Format 2 3 5 6
	if (is_mono(image)) {
		image->load = image_read_mono_data;
	} else {
		image->load = image_read_rgb_data;
	}
}

void image_read_mono_data(image_t *image, string_t buffer)
{
	int scalar = 1;

	if (image->type == 1 || image->type == 4) {
		scalar = 255;
	}

	image->data[image->read_y][image->read_x] =
			new_pixel_mono_color(is_binary(image) ?
								 (int)buffer[0] :
								 strtol(buffer, NULL, 10) * scalar);

	image->read_x++;
	if (image->read_x == image->width) {
		image->read_x = 0;
		image->read_y++;
	}

	if (image->read_y == image->height) {
		image->state = IMAGE_LOADED;
	}
}

void image_read_rgb_data(image_t *image, string_t buffer)
{
	switch (image->state) {
		case IMAGE_READ_DATA:
		case IMAGE_READ_DATA_RED:
			image->data[image->read_y][image->read_x].red = is_binary(image) ?
															(int)buffer[0] :
															strtol(buffer, NULL, 10);
			image->state = IMAGE_READ_DATA_GREEN;
			break;
		case IMAGE_READ_DATA_GREEN:
			image->data[image->read_y][image->read_x].green = is_binary(image) ?
															  (int)buffer[0] :
															  strtol(buffer, NULL, 10);
			image->state = IMAGE_READ_DATA_BLUE;
			break;
		case IMAGE_READ_DATA_BLUE:
			image->data[image->read_y][image->read_x].blue = is_binary(image) ?
															 (int)buffer[0] :
															 strtol(buffer, NULL, 10);
			image->state = IMAGE_READ_DATA_RED;

			image->read_x++;
			if (image->read_x == image->width) {
				image->read_x = 0;
				image->read_y++;
			}

			if (image->read_y == image->height) {
				image->state = IMAGE_LOADED;
			}
			break;
	}
}

bool is_mono(image_t *image)
{
	return image->type == 1 || image->type == 2 || image->type == 4 || image->type == 5;
}

pixel_t new_pixel_mono_color(uint8_t color)
{
	pixel_t output;

	output.red = color;
	output.green = color;
	output.blue = color;

	return output;
}

pixel_t new_pixel_color(uint8_t red, uint8_t green, uint8_t blue)
{
	pixel_t output;

	output.red = red;
	output.green = green;
	output.blue = blue;

	return output;
}

void free_image_pointer(image_t *image)
{
	free_image(*image);
	free(image);
}

void free_image(image_t image)
{
	for (size_t i = 0; i < image.height; i++) {
		free(image.data[i]);
	}

	free(image.data);
}

image_t new_empty_image()
{
	image_t image;

	image.type = 0;

	image.width = 0;
	image.height = 0;

	image.data = NULL;

	image.selection_start = new_position(0, 0);
	image.selection_end = new_position(0, 0);

	// TODO Maybe remove at some point
	// image.max_data_value = 0;

	image.read_x = 0;
	image.read_y = 0;
	image.state = IMAGE_NOT_LOADED;

	image.load = NULL;

	return image;
}

bool is_reading_binary(image_t *image)
{
	bool flag1 = is_binary(image);
	bool flag2 = image->state == IMAGE_READ_DATA ||
				 image->state == IMAGE_READ_DATA_RED ||
				 image->state == IMAGE_READ_DATA_GREEN ||
				 image->state == IMAGE_READ_DATA_BLUE;

	return flag1 && flag2;
}

bool is_binary(image_t *image)
{
	return image->type == 4 || image->type == 5 || image->type == 6;
}

position_t new_position(uint32_t x, uint32_t y)
{
	position_t position;

	position.x = x;
	position.y = y;

	return position;
}

int set_selection(image_t *image, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
	if (image->state == IMAGE_NOT_LOADED) {
		return 2;
	}

	// The (-1)s are because the specification stats that the selection is
	// inclusive to the left and top and exclusive to the right
	// [x1, x2) [y1, y2)

	x2--;
	y2--;

	uint32_t real_x1 = min(x1, x2);
	uint32_t real_x2 = max(x1, x2);
	uint32_t real_y1 = min(y1, y2);
	uint32_t real_y2 = max(y1, y2);

	if (x1 >= image->width || x2 > image->width || y1 >= image->height || y2 > image->height) {
		return 1;
	}

	image->selection_start = new_position(real_x1, real_y1);
	image->selection_end = new_position(real_x2, real_y2);

	return 0;
}

uint32_t *generate_histogram(image_t *image)
{
	uint32_t *histogram = calloc(255, sizeof(uint32_t));

	for (size_t i = image->selection_start.y; i <= image->selection_end.y; i++) {
		for (size_t j = image->selection_start.x; j <= image->selection_end.x; j++) {
			histogram[image->data[i][j].red]++;
		}
	}

	return histogram;
}

void print_histogram(image_t *image, uint32_t max_stars, uint32_t bins)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return;
	}

	if (!is_mono(image)) {
		printf("Black and white image needed\n");
		return;
	}

	uint32_t *histogram = generate_histogram(image);

	uint32_t *binned_histogram = calloc(bins, sizeof(uint32_t));

	uint32_t elements_per_bin = 256 / bins;

	uint32_t max_value = 0;

	for (int bin_index = 0; bin_index < bins; bin_index++) {
		for (int element_index = 0; element_index < elements_per_bin; element_index++) {
			binned_histogram[bin_index] += histogram[bin_index * elements_per_bin + element_index];

			if (binned_histogram[bin_index] > max_value) {
				max_value = binned_histogram[bin_index];
			}
		}
	}

	for (int i = 0; i < bins; i++) {
		int stars = (int)(1.0 * binned_histogram[i] * max_stars / max_value);

		// printf("%d [%3d, %3d): ", stars, i * elements_per_bin, (i + 1) * elements_per_bin);
		printf("%d\t|\t", stars);

		for (int j = 0; j < stars; j++) {
			printf("*");
		}
		printf("\n");
	}

	free(histogram);
	free(binned_histogram);
}

void equalize(image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return;
	}

	if (!is_mono(image)) {
		printf("Black and white image needed\n");
		return;
	}

	uint32_t *histogram = generate_histogram(image);

	for (int i = 0; i < 256; i++) {
		if (histogram[i] != 0)
			printf("%d -> %d\n", i, histogram[i]);
	}

	double area_reversed = 1.0 / ((image->selection_end.x - image->selection_start.x + 1) *
								  (image->selection_end.y - image->selection_start.y + 1));

	printf("%d\n", ((image->selection_end.x - image->selection_start.x + 1) *
					(image->selection_end.y - image->selection_start.y + 1)));
	printf("%f\n", area_reversed);

	for (uint32_t y = image->selection_start.y; y <= image->selection_end.y; y++)
		for (uint32_t x = image->selection_start.x; x <= image->selection_end.x; x++) {
			uint32_t sum = 0;

			for (uint32_t i = 0; i <= image->data[y][x].red; i++)
				sum += histogram[i];

			image->data[y][x].red = (uint8_t)round(255.0 * area_reversed * sum);
			image->data[y][x].red = clamp(image->data[y][x].red, 0, 255);
		}

	printf("Equalize done\n");
}

void save_image(image_t *image, FILE *file)
{
	fprintf(file, "P%d\n", image->type);
	fprintf(file, "%zu %zu\n", image->width, image->height);

	if (image->type == 1 || image->type == 4) {
		fprintf(file, "1\n");
	} else {
		fprintf(file, "255\n");
	}

	for (size_t i = 0; i < image->height; i++) {
		for (size_t j = 0; j < image->width; j++) {
			if (is_mono(image)) {
				fprintf(file, "%d ", image->data[i][j].red);
			} else {
				fprintf(file, "%d %d %d ", image->data[i][j].red, image->data[i][j].green, image->data[i][j].blue);
			}
		}
		fprintf(file, "\n");
	}
}