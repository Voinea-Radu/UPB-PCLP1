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

#define MAX_ARGUMENT_SIZE 100

#define UNKNOWN_COMMAND (-1)
#define LOAD 1
#define SELECT 2
#define EXIT 100

static string_to_handle command_table[] = {
		{"print", handle_print},
		{"load",  handle_load},
		{"exit",  handle_exit}
};

int process_command(string_t command)
{
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

	printf("Unknown command: %s\n", command);

	return UNKNOWN_COMMAND;
}

int handle_load(image_t *image)
{
	string_t file_name = read_string(MAX_ARGUMENT_SIZE, stdin);

	printf("Loading %s...\n", file_name);

	FILE *file = fopen(file_name, "r");

	if (NULL == file) {
		printf("Failed to load %s\n", file_name);
		image->state = IMAGE_NOT_LOADED;
		return CONTINUE;
	}

	free_image(*image);
	*image = load_image(file);


	if(image->state == IMAGE_LOADED)
		printf("Loaded %s\n", file_name);
	else
		printf("Failed to load %s\n", file_name);

	free(file_name);
	fclose(file);

	return CONTINUE;
}

int handle_print(image_t *image)
{
	printf("\n\n");

	printf("Type: %d\nMax value: %zu\nSize: %zux%zu\nData:\n", image->type, image->max_data_value, image->width,
		   image->height);
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