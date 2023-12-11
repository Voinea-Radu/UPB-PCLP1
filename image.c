/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include "image.h"

#define MAX_PGM_LINE_SIZE 70

t_image load_image(FILE* file){
	t_image output;

	// Read the magic number P1 or P6
	t_string type = read_string(2, file);
	type.data[0] = type.data[1];
	type.data[1] = '\0';

	output.type = atoi(type.data);

	// Read the file line by line until the end
	// Ignore all the lines that start with #
	while (1) {
		t_string line = read_line(MAX_PGM_LINE_SIZE, file);

		if (line.data[0] == '#') {
			continue;
		}


		/*

		// Read the width and height
		if (output.width == 0) {
			t_string width = read_string(MAX_PGM_LINE_SIZE, file);
			t_string height = read_string(MAX_PGM_LINE_SIZE, file);

			output.width = atoi(width.data);
			output.height = atoi(height.data);

			// Read the max value
			t_string max_value = read_string(100, file);
			output.max_value = atoi(max_value.data);

			// Allocate memory for the image
			output.pixels = safe_malloc(output.width * output.height * sizeof(t_pixel));
		} else {
			// Read the pixels
			for (int i = 0; i < output.width * output.height; i++) {
				t_string pixel = read_string(100, file);

				if (output.type == 1) {
					output.pixels[i] = new_pixel_mono_color(atoi(pixel.data));
				} else {
					t_string red = read_string(100, file);
					t_string green = read_string(100, file);
					t_string blue = read_string(100, file);

					output.pixels[i] = new_pixel_color(atoi(red.data), atoi(green.data), atoi(blue.data));
				}
			}
		}

		if (feof(file)) {
			break;
		}

		*/
	}

	// Mark the image as loaded
	output.loaded = true;

	return output;
}

t_pixel new_pixel_mono_color(uint8_t color){
	t_pixel output;

	output.value = color;

	return output;
}

t_pixel new_pixel_color(uint8_t red, uint8_t green, uint8_t blue){
	t_pixel output;

	output.rgb.red = red;
	output.rgb.green = green;
	output.rgb.blue = blue;

	return output;
}