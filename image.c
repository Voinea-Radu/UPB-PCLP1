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
		data = fgetc(file);

		if (data == EOF) {
			break;
		}

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

		if (data == '\n' || data == ' ') {
			read_p1_format(&image, &buffer, &buffer_size);
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

void read_p1_format(image_t *image, string_t *buffer, size_t *buffer_size)
{

	switch (image->state) {
		case IMAGE_READ_PGM_TYPE:
			(*buffer)[0] = (*buffer)[1];
			(*buffer)[1] = '\0';
			image->type = (int)strtol(*buffer, NULL, 10);

			image->state = IMAGE_READ_WIDTH;
			reset_buffer(buffer, buffer_size);
			break;
		case IMAGE_READ_WIDTH:
			image->width = strtol(*buffer, NULL, 10);

			image->state = IMAGE_READ_HEIGHT;
			reset_buffer(buffer, buffer_size);
			break;
		case IMAGE_READ_HEIGHT:
			image->height = strtol(*buffer, NULL, 10);

			// Create the data matrix for the image
			image->data = malloc(image->height * sizeof(pixel_t *));
			for (size_t i = 0; i < image->height; i++) {
				image->data[i] = malloc(image->width * sizeof(pixel_t));
			}

			image->state = IMAGE_READ_DATA;
			reset_buffer(buffer, buffer_size);
			break;
		case IMAGE_READ_DATA:
			if (*buffer_size == 0) {
				break;
			}

			image->data[image->read_y][image->read_x] =
					new_pixel_mono_color(strtol(*buffer, NULL, 10));

			reset_buffer(buffer, buffer_size);

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

pixel_t new_pixel_mono_color(uint8_t color)
{
	pixel_t output;

	output.value = color;

	return output;
}

pixel_t new_pixel_color(uint8_t red, uint8_t green, uint8_t blue)
{
	pixel_t output;

	output.rgb.red = red;
	output.rgb.green = green;
	output.rgb.blue = blue;

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

	image.read_x = 0;
	image.read_y = 0;
	image.state = IMAGE_NOT_LOADED;

	return image;
}