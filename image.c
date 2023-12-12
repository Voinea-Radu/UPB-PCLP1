/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include "image.h"
#include "utils.h"

#define MAX_PGM_LINE_SIZE 70

// Image loading states
#define READ_PGM_TYPE 0
#define READ_WIDTH 1
#define READ_HEIGHT 2
#define READ_DATA 3
#define DONE 4

image_t load_image(FILE *file)
{
	int state = READ_PGM_TYPE;
	bool is_comment = false;

	image_t image;
	string_t buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
	int buffer_index = 0;

	size_t pixel_index = 0;

	char data;
	while (1){
		data = fgetc(file);

		if(data == EOF){
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

		printf("%c", data);
		buffer[buffer_index++] = data;

		if (data == '\n' || data == ' ') {
			switch (state) {
				case READ_PGM_TYPE:
					buffer[0] = buffer[1];
					buffer[1] = '\0';
					image.type = atoi(buffer);

					state = READ_WIDTH;
					buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
					buffer_index = 0;
					break;
				case READ_WIDTH:
					image.width = atoi(buffer);

					state = READ_HEIGHT;
					buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
					buffer_index = 0;
					break;
				case READ_HEIGHT:
					image.height = atoi(buffer);

					image.data = malloc(image.height * sizeof(pixel_t *));
					for (size_t i = 0; i < image.height; i++) {
						image.data[i] = malloc(image.width * sizeof(pixel_t));
					}

					state = READ_DATA;
					buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
					buffer_index = 0;
					break;
				case READ_DATA:

					image.data[pixel_index / image.width][pixel_index % image.width] = new_pixel_mono_color(atoi(buffer));
					pixel_index++;

					if (pixel_index == image.width * image.height) {
						state = DONE;
					}
					break;
			}
		}

		if (state == DONE) {
			break;
		}
	}

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