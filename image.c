/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include "image.h"
#include "utils.h"

// Image loading states

image_t load_image(FILE *file)
{
	bool is_comment = false;

	string_t buffer = NULL;
	size_t buffer_size = 0;

	reset_buffer(&buffer, &buffer_size);

	image_t image = new_image();

	image.state = IMAGE_READ_PGM_TYPE;

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

		if (is_reading_binary(&image)) {
			buffer[buffer_size++] = data;
			buffer[buffer_size] = '\0';
		}

		if (data == '\n' || data == ' ' || is_reading_binary(&image)) {
			if (image.state == IMAGE_READ_PGM_TYPE) {
				buffer[0] = buffer[1];
				buffer[1] = '\0';
				image.type = (int)strtol(buffer, NULL, 10);

				image.state = IMAGE_LOADING;
				reset_buffer(&buffer, &buffer_size);

				image.load = image_read_width;
				continue;
			}

			if (buffer_size == 0) {
				continue;
			}

			image.load(&image, buffer);
			reset_buffer(&buffer, &buffer_size);
		} else {
			buffer[buffer_size++] = data;
			buffer[buffer_size] = '\0';
		}

		if (image.state == IMAGE_LOADED) {
			break;
		}
	}

	free(buffer);
	return image;
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

	image->load = image_read_max_value;
}

void image_read_max_value(image_t *image, string_t buffer)
{
	image->state = IMAGE_READ_DATA;

	if (image->type == 1) {
		image->max_data_value = 1;
		if (is_mono(image)) {
			image_read_mono_data(image, buffer);
		} else {
			image_read_rgb_data(image, buffer);
		}
		return;
	}

	image->max_data_value = strtol(buffer, NULL, 10);

	if (is_mono(image)) {
		image->load = image_read_mono_data;
	} else {
		image->load = image_read_rgb_data;
	}
}

void image_read_mono_data(image_t *image, string_t buffer)
{
	image->data[image->read_y][image->read_x] =
			new_pixel_mono_color(is_binary(image) ?
								 (int)buffer[0] :
								 strtol(buffer, NULL, 10));

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

image_t new_image()
{
	image_t image;

	image.type = 0;
	image.width = 0;
	image.height = 0;
	image.data = NULL;
	image.max_data_value = 0;

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
