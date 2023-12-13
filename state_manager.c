/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <argz.h>
#include "state_manager.h"
#include "string_utils.h"
#include "image.h"
#include "utils.h"

#define MAX_ARGUMENT_SIZE 100

#define UNKNOWN_COMMAND (-1)
#define LOAD 1
#define SELECT 2
#define QUIT 100

static string_pair command_table[] = {
		{"LOAD",   LOAD},
		{"load",   LOAD}, // TODO Remove
		{"SELECT", SELECT},
		{"select", SELECT}, // TODO Remove
		{"QUIT", QUIT},
		{"quit", QUIT} // TODO Remove
};

#define COMMAND_TABLE_SIZE (sizeof(command_table)/sizeof(string_pair))

int get_command_id(char *key)
{
	for (size_t i = 0; i < COMMAND_TABLE_SIZE; i++) {
		string_pair pair = command_table[i];
		if (strcmp(pair.key, key) == 0)
			return pair.value;
	}

	return UNKNOWN_COMMAND;
}

int process_command(string_t command)
{
	static image_t *image = NULL;

	if (image == NULL) {
		image = safe_calloc(sizeof(image_t));
	}

	switch (get_command_id(command)) {
		case LOAD:
			handle_load(image);

			printf("\n\n");

			printf("Max value: %zu\nSize: %zux%zu\nData:\n", image->max_data_value, image->width, image->height);
			for(size_t i = 0; i < image->height; i++){
				for(size_t j = 0; j < image->width; j++){
					printf("(%d %d %d) ", image->data[i][j].red, image->data[i][j].green, image->data[i][j].blue);
				}
				printf("\n");
			}

			break;
		case SELECT:
			printf("SELECT\n");
			break;
		case QUIT:
			printf("QUIT\n");
			free_image_pointer(image);
			return EXIT;
		case UNKNOWN_COMMAND:
		default:
			printf("UNKNOWN COMMAND\n");

	}

	return CONTINUE;
}

void handle_load(image_t *image)
{
	string_t file_name = read_string(MAX_ARGUMENT_SIZE, stdin);

	printf("Loading %s...\n", file_name);

	FILE* file = fopen(file_name, "r");

	if (NULL == file) {
		printf("Failed to load %s\n", file_name);
		image->state = IMAGE_NOT_LOADED;
		return;
	}

	free(file_name);
	free_image(*image);
	*image = load_image(file);

	fclose(file);
}