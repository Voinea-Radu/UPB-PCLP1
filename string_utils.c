/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include <stdbool.h>
#include "string_utils.h"
#include "utils.h"


string_t generic_read_string(int max_size, FILE *stream, char *separators)
{
	string_t data = safe_malloc(max_size * sizeof(char));
	int actual_size = 0;

	while (1) {
		char current_char = (char)fgetc(stream);

		bool is_separator = false;

		if (current_char == EOF) {
			data[actual_size] = current_char;
			actual_size++;
			break;
		}

		for (size_t i = 0; i < strlen(separators); i++) {
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

	return data;
}

string_t read_string(int max_size, FILE *stream)
{
	return generic_read_string(max_size, stream, " \n");
}

string_t read_line(int max_size, FILE *stream)
{
	return generic_read_string(max_size, stream, "\n");
}

string_t *split_string(string_t data, string_t separator, size_t *size)
{
	string_t string_data = malloc(strlen(data) * sizeof(char));
	strcpy(string_data, data);

	string_t split;

	// Get the number of elements after the split
	strtok(string_data, separator);
	(*size) = 1;
	while (strtok(NULL, separator) != NULL) {
		(*size)++;
	}

	// Create the array of strings
	string_t *result = malloc(sizeof(string_t) * (*size));
	int index = 0;

	strcpy(string_data, data);
	split = strtok(string_data, separator);
	while (split != NULL) {
		result[index++] = split;
		split = strtok(NULL, separator);
	}

	return result;
}

void reset_buffer(string_t buffer, size_t *buffer_size)
{
	*buffer_size = 0;
	buffer[0] = '\0';
}


