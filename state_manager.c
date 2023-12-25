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
		{"save",            handle_save}, // TODO Chane. This is not to spec. Only for debug purposes as of now
		{"load",            handle_load},
		{"crop",            handle_crop},
		{"rotate",          handle_rotate},
		{"apply",           handle_apply},
		{"histogram",       handle_histogram},
		{"equalize",        handle_equalize},
		{"select",          handle_select},
		{"exit",            handle_exit},
		{"quit",            handle_exit} // Only for debug purposes
};

void process_instructions(instructions_t instructions)
{
	image_t *image = NULL;

	if (image == NULL) {
		image = safe_calloc(sizeof(image_t));
	}

	string_t command = get_next_instruction(&instructions);
	while (command != NULL) {
		int code = process_command(&instructions, command, image);

		if (code == EXIT) {
			break;
		}

		command = get_next_instruction(&instructions);
	}

	free_image_pointer(image);
}

int process_command(instructions_t *instructions, string_t command, image_t *image)
{
	static const size_t size = sizeof(command_table) / sizeof(string_to_handle);

	for (size_t i = 0; i < size; i++) {
		string_to_handle pair = command_table[i];

		to_lower(command);

		if (strcmp(pair.key, command) == 0)
			return pair.handle(instructions, image);
	}

	printf("Unknown command: '%s'\n", command);

	return UNKNOWN_COMMAND;
}

int handle_load(instructions_t *instructions, image_t *image)
{
	string_t file_name = get_next_instruction(instructions);

	FILE *file = fopen(file_name, "r");

	if (NULL == file) {
		printf("Failed to load %s\n", file_name);
		image->state = IMAGE_NOT_LOADED;
		return CONTINUE;
	}

	free_image(*image);
	*image = new_image(file);

	if (image->state == IMAGE_LOADED)
		printf("Loaded %s\n", file_name);
	else {
		printf("Failed to load %s\n", file_name);
		image->state = IMAGE_NOT_LOADED;
	}

	fclose(file);

	return CONTINUE;
}

int handle_save(instructions_t *instructions, image_t *image)
{
	string_t file_name = get_next_instruction(instructions);
	string_t type = get_next_instruction(instructions);// TODO Implement

	if (type == NULL || strcmp(type, "ascii") != 0) {
		type = "binary";
		move_cursor(instructions, -1);
	}


	FILE *file;

	if (strcmp(type, "binary") == 0){
		 file = fopen(file_name, "wb");

		if (NULL == file) {
			printf("Failed to save %s\n", file_name);
			return CONTINUE;
		}

		save_image_binary(image, file);
	}else{
		 file = fopen(file_name, "w");

		if (NULL == file) {
			printf("Failed to save %s\n", file_name);
			return CONTINUE;
		}

		save_image_ascii(image, file);
	}

	printf("Saved %s\n", file_name);

	fclose(file);

	return CONTINUE;
}

int handle_convert_to_mono(instructions_t *instructions, image_t *image)
{
	if (image->type == 3) {
		image->type = 2;
	} else if (image->type == 6) {
		image->type = 5;
	}

	printf("Converted to mono\n");

	return CONTINUE;
}

int handle_print(instructions_t *instructions, image_t *image)
{
	printf("\n\n");

	printf("Type: %d\n", image->type);
	printf("Size: %zux%zu\n", image->width, image->height);
	printf("Selected: [%u %u] -> [%u %u]\n", image->selection_start.x,
		   image->selection_start.y, image->selection_end.x,
		   image->selection_end.y);
	printf("Data:\n");
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

int handle_exit(instructions_t *instructions, image_t *image)
{
	free_image_pointer(image);
	return EXIT;
}

int handle_select(instructions_t *instructions, image_t *image)
{
	uint32_t x1, y1, x2, y2;

	string_t arg_1 = get_next_instruction(instructions);

	bool select_all = false;

	to_lower(arg_1);

	if (strcmp(arg_1, "all") == 0) {
		x1 = 0;
		y1 = 0;
		x2 = image->width;
		y2 = image->height;
		select_all = true;
	} else {
		x1 = strtol(arg_1, NULL, 10);
		y1 = strtol(get_next_instruction(instructions), NULL, 10);
		x2 = strtol(get_next_instruction(instructions), NULL, 10);
		y2 = strtol(get_next_instruction(instructions), NULL, 10);
	}

	int result = set_selection(image, x1, y1, x2, y2);

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
		case 2:
			printf("No image loaded\n");
			break;
	}

	return CONTINUE;
}

int handle_histogram(instructions_t *instructions, image_t *image)
{
	uint32_t max_stars = strtol(get_next_instruction(instructions), NULL, 10);
	uint32_t bins = strtol(get_next_instruction(instructions), NULL, 10);

	if (bins < 2 || !is_power_of_two(bins)) {
		printf("Invalid number of bins\n");
		return CONTINUE;
	}

	print_histogram(image, max_stars, bins);

	return CONTINUE;
}

int handle_equalize(instructions_t *instructions, image_t *image)
{
	equalize(image);
	return CONTINUE;
}

int handle_rotate(instructions_t *instructions, image_t *image)
{
	int16_t degrees = strtol(get_next_instruction(instructions), NULL, 10);

	rotate(image, degrees);

	return CONTINUE;
}

int handle_crop(instructions_t *instructions, image_t *image)
{
	crop(image);

	return CONTINUE;
}

int handle_apply(instructions_t *instructions, image_t *image)
{
	string_t filter_name = get_next_instruction(instructions);

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