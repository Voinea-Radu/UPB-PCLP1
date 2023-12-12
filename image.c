/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include "image.h"
#include "utils.h"

#define MAX_PGM_LINE_SIZE 70

// Image loading states
#define READ_PGM_TYPE 0
#define READ_WIDTH 1
#define READ_HEIGHT 2
#define READ_DATA 3
#define DONE 4

void reset_buffer(string_t *buffer, int *buffer_index)
{
	*buffer_index = 0;

	if (buffer != NULL)
		free(*buffer);

	*buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
}

image_t load_image(FILE *file)
{
	int state = READ_PGM_TYPE;
	bool is_comment = false;

	image_t image;

	string_t buffer = NULL;
	int buffer_index = 0;

	reset_buffer(&buffer, &buffer_index);

	size_t pixel_index = 0;

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

		//printf("%c", data);

		if (data == '\n' || data == ' ') {
			switch (state) {
				case READ_PGM_TYPE:
					buffer[0] = buffer[1];
					buffer[1] = '\0';
					image.type = (int)strtol(buffer, NULL, 10);

					state = READ_WIDTH;
					reset_buffer(&buffer, &buffer_index);
					break;
				case READ_WIDTH:
					image.width = strtol(buffer, NULL, 10);

					state = READ_HEIGHT;
					reset_buffer(&buffer, &buffer_index);
					break;
				case READ_HEIGHT:
					image.height = strtol(buffer, NULL, 10);

					// Create the data matrix for the image
					image.data = malloc(image.height * sizeof(pixel_t *));
					for (size_t i = 0; i < image.height; i++) {
						image.data[i] = malloc(image.width * sizeof(pixel_t));
					}

					state = READ_DATA;
					reset_buffer(&buffer, &buffer_index);
					break;
				case READ_DATA:
					if (buffer_index == 0) {
						continue;
					}

					image.data
					[pixel_index / image.width]
					[pixel_index % image.width] =
							new_pixel_mono_color(strtol(buffer, NULL, 10));
					pixel_index++;

					reset_buffer(&buffer, &buffer_index);

					if (pixel_index == image.width * image.height) {
						state = DONE;
					}
					break;
			}
		} else {
			buffer[buffer_index++] = data;
			buffer[buffer_index] = '\0';
		}

		if (state == DONE) {
			break;
		}
	}

	free(buffer);
	return image;
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

