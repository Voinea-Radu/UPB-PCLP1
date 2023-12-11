/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <argz.h>
#include "state_manager.h"
#include "string_utils.h"
#include "image.h"

#define MAX_ARGUMENT_SIZE 100

#define UNKNOWN_COMMAND (-1)
#define LOAD 1
#define SELECT 2

static string_pair command_table[] = {
		{"LOAD",   LOAD},
		{"SELECT", SELECT}
};

#define COMMAND_TABLE_SIZE (sizeof(command_table)/sizeof(string_pair))

int get_command_id(char *key)
{

	for (int i = 0; i < COMMAND_TABLE_SIZE; i++) {
		string_pair pair = command_table[i];
		if (strcmp(pair.key, key) == 0)
			return pair.value;
	}

	return UNKNOWN_COMMAND;
}

void process_command(t_string command)
{
	static t_image image;

	switch (get_command_id(command.data)) {
		case LOAD:
			handle_load(&image);
			break;
		case SELECT:
			printf("SELECT\n");
			break;
		case UNKNOWN_COMMAND:
		default:
			printf("UNKNOWN COMMAND\n");

	}
}

void handle_load(t_image *image)
{
	t_string file_name = read_string(MAX_ARGUMENT_SIZE, stdin);

	printf("Loading '%s'...\n", file_name.data);

	FILE* file = fopen(file_name.data, "r");

	if (NULL == file) {
		printf("Failed to load '%s'\n", file_name.data);
		image->loaded = 0;
		return;
	}

	*image = load_image(file);
}