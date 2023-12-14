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
		{"print",  handle_print},
		{"load",   handle_load},
		{"select", handle_select},
		{"exit",   handle_exit},
		{"quit",   handle_exit}
};

int process_command(string_t command)
{
	if (strcmp(command, " ") == 0 || strcmp(command, "\n") == 0 || strcmp(command, "") == 0)
		return CONTINUE;

	static image_t *image = NULL;

	if (image == NULL) {
		image = safe_calloc(sizeof(image_t));
	}

	static const size_t size = sizeof(command_table) / sizeof(string_to_handle);

	for (size_t i = 0; i < size; i++) {
		string_to_handle pair = command_table[i];

		to_lower(command);

		if (strcmp(pair.key, command) == 0)
			return pair.handle(image);
	}

	printf("Unknown command: '%s'\n", command);

	return UNKNOWN_COMMAND;
}

int handle_load(image_t *image)
{
	string_t file_name = read_string(MAX_ARGUMENT_SIZE, stdin);

	//printf("Loading %s...\n", file_name);

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

	free(file_name);
	fclose(file);

	return CONTINUE;
}

int handle_print(image_t *image)
{
	printf("\n\n");

	printf("Type: %d\n", image->type);
	printf("Max value: %zu\n", image->max_data_value);
	printf("Size: %zux%zu\n", image->width, image->height);
	printf("Selected: [%u %u] -> [%u %u]\n", image->selection_start.x, image->selection_start.y, image->selection_end.x,
		   image->selection_end.y);
	printf("Data:\n");
	for (size_t i = 0; i < image->height; i++) {
		for (size_t j = 0; j < image->width; j++) {
			printf("(%3d %3d %3d) ", image->data[i][j].red, image->data[i][j].green, image->data[i][j].blue);
		}
		printf("\n");
	}
	return CONTINUE;
}

int handle_exit(image_t *image)
{
	free_image_pointer(image);
	return EXIT;
}

int handle_select(image_t *image)
{
	uint32_t x1, y1, x2, y2;
	scanf("%u %u %u %u", &x1, &y1, &x2, &y2);

	int result = set_selection(image, x1, y1, x2, y2);

	switch (result) {
		case 0:
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