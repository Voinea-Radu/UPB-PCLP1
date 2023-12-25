/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <argz.h>
#include "state_manager.h"
#include "string_utils.h"
#include "image.h"
#include "utils.h"
#include <ctype.h>


static string_to_handle command_table[] = {
		{"print",           handle_print}, // Only for debug purposes
		{"convert_to_mono", handle_convert_to_mono}, // Only for debug purposes
		{"save",            handle_save},
		{"load",            handle_load},
		{"crop",            handle_crop},
		{"rotate",          handle_rotate},
		{"apply",           handle_apply},
		{"histogram",       handle_histogram},
		{"equalize",        handle_equalize},
		{"select",          handle_select},
		{"debug",           handle_debug},
		{"exit",            handle_exit},
		{"quit",            handle_exit} // Only for debug purposes
};


int process_command(string_t instruction)
{
	static const size_t size = sizeof(command_table) / sizeof(string_to_handle);
	static image_t *image = NULL;

	int output = UNKNOWN_COMMAND;

	if (image == NULL) {
		image = safe_calloc(sizeof(image_t));
	}

	int args_size = 0;
	string_t *args = split_string(&args_size, instruction, ' ');

	to_lower(args[0]);

	for (size_t i = 0; i < size; i++) {
		string_to_handle pair = command_table[i];

		if (strcmp(pair.key, args[0]) == 0) {
			output = pair.handle(args, args_size, image);
		}
	}

	free_matrix(args, args_size);

	if (UNKNOWN_COMMAND == output) {
		printf("Invalid command\n");
	}

	return output;
}

int handle_load(string_t *args, int args_size, image_t *image)
{
	string_t file_name = args[1];

	FILE *file = fopen(file_name, "r");

	if (NULL == file) {
		printf("Failed to load %s\n", file_name);
		image->state = IMAGE_NOT_LOADED;
		return CONTINUE;
	}

	free_image(*image);
	*image = new_image(file);


	if (image->state == IMAGE_LOADED) {
		printf("Loaded %s\n", file_name);
	} else {
		printf("Failed to load %s\n", file_name);
		image->state = IMAGE_NOT_LOADED;
	}

	fclose(file);

	return CONTINUE;
}

int handle_save(string_t *args, int args_size, image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return CONTINUE;
	}

	string_t file_name = args[1];
	string_t type = "binary";
	if (args_size == 3) {
		type = args[2];
	}

	FILE *file = fopen(file_name, "w");

	if (NULL == file) {
		printf("Failed to save %s\n", file_name);
		return CONTINUE;
	}

	if (strcmp(type, "binary") == 0) {
		save_image_binary(image, file);
	} else {
		save_image_ascii(image, file);
	}

	printf("Saved %s\n", file_name);

	fclose(file);

	return CONTINUE;
}

int handle_convert_to_mono(string_t *args, int args_size, image_t *image)
{
	if (image->type == 3) {
		image->type = 2;
	} else if (image->type == 6) {
		image->type = 5;
	}

	printf("Converted to mono\n");

	return CONTINUE;
}

int handle_print(string_t *args, int args_size, image_t *image)
{
	printf("\n\n");

	if (args_size == 3) {
		int x = strtol(args[1], NULL, 10);
		int y = strtol(args[2], NULL, 10);

		if (x < 0 || x >= image->width || y < 0 || y >= image->height) {
			printf("Invalid coordinates\n");
			return CONTINUE;
		}

		if (is_mono(image)) {
			printf("%3d\n", image->data[y][x].red);
		} else {
			printf("(%3d %3d %3d)\n", image->data[y][x].red,
				   image->data[y][x].green, image->data[y][x].blue);
		}

		return CONTINUE;
	}

	printf("Type: %d\n", image->type);
	printf("Size: %zux%zu\n", image->width, image->height);
	printf("Selected: [%u %u] -> [%u %u]\n", image->selection_start.x,
		   image->selection_start.y, image->selection_end.x,
		   image->selection_end.y);
	printf("Data:\n");

	if (args_size == 2) {
		if (strcmp(args[1], "meta") == 0) {
			return CONTINUE;
		}
	}

	for (size_t i = 0; i < image->height; i++) {
		for (size_t j = 0; j < image->width; j++) {
			if (is_mono(image)) {
				printf("%3d ", image->data[i][j].red);
			} else {
				printf("(%3d %3d %3d) ", image->data[i][j].red,
					   image->data[i][j].green, image->data[i][j].blue);
			}
		}
		printf("\n");
	}
	return CONTINUE;
}

int handle_exit(string_t *args, int args_size, image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
	}

	free_image_pointer(image);
	return EXIT;
}

int handle_select(string_t *args, int args_size, image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return CONTINUE;
	}

	uint32_t x1, y1, x2, y2;

	bool select_all = false;

	to_lower(args[1]);

	if (strcmp(args[1], "all") == 0) {
		x1 = 0;
		y1 = 0;
		x2 = image->width;
		y2 = image->height;
		select_all = true;
	} else {
		if (args_size != 5) {
			printf("Invalid command\n");
			return CONTINUE;
		}

		for (int i = 1; i < args_size; i++) {
			if (!is_number(args[i])) {
				printf("Invalid command\n");
				return CONTINUE;
			}
		}

		x1 = strtol(args[1], NULL, 10);
		y1 = strtol(args[2], NULL, 10);
		x2 = strtol(args[3], NULL, 10);
		y2 = strtol(args[4], NULL, 10);
	}

	int result = set_selection(image, &x1, &y1, &x2, &y2);

	switch (result) {
		case 0:
			if (select_all) {
				printf("Selected ALL\n");
				break;
			}
			printf("Selected %u %u %u %u\n", x1, y1, x2, y2);
			break;
		case 1:
			printf("Invalid set of coordinates\n");
			break;
	}

	return CONTINUE;
}

int handle_histogram(string_t *args, int args_size, image_t *image)
{
	if(image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return CONTINUE;
	}

	if (args_size != 3) {
		printf("Invalid command\n");
		return CONTINUE;
	}

	for (int i = 1; i < args_size; i++) {
		if (!is_number(args[i])) {
			printf("Invalid command\n");
			return CONTINUE;
		}
	}

	uint32_t max_stars = strtol(args[1], NULL, 10);
	uint32_t bins = strtol(args[2], NULL, 10);

	if (bins < 2 || !is_power_of_two(bins)) {
		printf("Invalid number of bins\n");
		return CONTINUE;
	}

	print_histogram(image, max_stars, bins);

	return CONTINUE;
}

int handle_equalize(string_t *args, int args_size, image_t *image)
{
	equalize(image);
	return CONTINUE;
}

int handle_rotate(string_t *args, int args_size, image_t *image)
{
	int16_t degrees = strtol(args[1], NULL, 10);

	rotate(image, degrees);

	return CONTINUE;
}

int handle_crop(string_t *args, int args_size, image_t *image)
{
	crop(image);

	return CONTINUE;
}

int handle_apply(string_t *args, int args_size, image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return CONTINUE;
	}

	if (args_size != 2) {
		printf("Invalid command\n");
		return CONTINUE;
	}

	string_t filter_name = args[1];

	to_lower(filter_name);

	bool result = 0;

	if (strcmp(filter_name, "edge") == 0) {
		result = apply_filter(image, EDGE_FILTER, EDGE_FILTER_FACTOR);
	} else if (strcmp(filter_name, "sharpen") == 0) {
		result = apply_filter(image, SHARPEN_FILTER, SHARPEN_FILTER_FACTOR);
	} else if (strcmp(filter_name, "blur") == 0) {
		result = apply_filter(image, BLUR_FILTER, BLUR_FILTER_FACTOR);
	} else if (strcmp(filter_name, "gaussian_blur") == 0) {
		result = apply_filter(image, GAUSSIAN_BLUR_FILTER,
							  GAUSSIAN_BLUR_FILTER_FACTOR);
	} else {
		printf("APPLY parameter invalid\n");
	}

	to_upper(filter_name);

	if (result) {
		printf("APPLY %s done\n", filter_name);
	}

	return CONTINUE;
}

int handle_debug(string_t *args, int args_size, image_t *image)
{
	printf("%d %d %d\n", image->data[100][149].red, image->data[100][149].green,
		   image->data[100][149].blue);

	return CONTINUE;
}