/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "string_utils.h"
#include "utils.h"


string_t generic_read_string(int max_size, FILE *stream, char *separators)
{

}

string_t read_line(int max_size, FILE *stream)
{
	string_t data = safe_malloc(max_size * sizeof(char));
	int size = 0;

	while (1) {
		char current_char = (char)fgetc(stream);

		bool is_separator = false;

		if (current_char == EOF) {
			if(size==0){
				free(data);
				return NULL;
			}
			break;
		}

		if (current_char == '\n') {
			is_separator = true;
			break;
		}

		data[size++] = current_char;
	}

	data[size] = '\0';

	return data;
}

string_t* split_string(int* size, string_t string, char separator){
	string_t* result = safe_malloc(sizeof(string_t) * strlen(string));
	int result_size = 0;

	string_t buffer = safe_malloc(strlen(string) * sizeof(char));
	size_t buffer_size = 0;

	for (size_t i = 0; i < strlen(string); i++) {
		if (string[i] == separator) {
			if (buffer_size == 0) {
				continue;
			}

			buffer[buffer_size] = '\0';
			result[result_size++] = buffer;
			buffer = safe_malloc(strlen(string) * sizeof(char));
			buffer_size = 0;
		} else {
			buffer[buffer_size++] = string[i];
		}
	}

	if (buffer_size != 0) {
		buffer[buffer_size] = '\0';
		result[result_size++] = buffer;
	}

	*size = result_size;

	return result;
}

void reset_buffer(string_t buffer, size_t *buffer_size)
{
	*buffer_size = 0;
	buffer[0] = '\0';
}

void to_lower(string_t string)
{
	size_t size = strlen(string);

	for (size_t i = 0; i < size; i++) {
		string[i] = (char)tolower(string[i]);
	}
}

void to_upper(string_t string)
{
	size_t size = strlen(string);

	for (size_t i = 0; i < size; i++) {
		string[i] = (char)toupper(string[i]);
	}
}

