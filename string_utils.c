/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string_utils.h"

t_string generic_read_string(int max_size, FILE *stream, char *separators)
{
	char *data = safe_malloc(max_size * sizeof(char));
	int actual_size = 0;

	while (1) {
		char current_char = (char)fgetc(stream);

		bool is_separator = false;

		for (int i = 0; i < strlen(separators); i++) {
			if (current_char == separators[i]) {
				is_separator = true;
				break;
			}
		}

		if (is_separator) {
			break;
		}

		data[actual_size] = current_char;
		actual_size++;
	}

	data[actual_size] = '\0';

	t_string result;
	result.data = data;

	return result;
}

t_string read_string(int max_size, FILE *stream)
{
	return generic_read_string(max_size, stream, " \n");
}

t_string read_line(int max_size, FILE *stream)
{
	return generic_read_string(max_size, stream, "\n");
}

t_string *split_string(t_string string, char *separator, int *size)
{
	char *string_data = malloc(strlen(string.data) * sizeof(char));
	strcpy(string_data, string.data);

	char *split;
	split = strtok(string_data, separator);

	while (split != NULL) {
		printf("%s\n", split);
		split = strtok(NULL, separator);
		(*size)++;
	}

	strcpy(string_data, string.data);

	split = strtok(string_data, separator);

	t_string *result = malloc(sizeof(t_string) * (*size));
	int index = 0;

	while (split != NULL) {
		printf("%s\n", split);
		split = strtok(NULL, separator);
		result[index].data = split;
		index++;
	}

	printf("=======\n");
	printf("%s\n", string_data);

	return NULL;
}

void *safe_malloc(size_t size)
{
	void *result = malloc(size);

	if (result == NULL) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}
