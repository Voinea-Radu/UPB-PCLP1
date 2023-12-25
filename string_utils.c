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

		for (size_t i = 0; i < strlen(separators); i++) {
			if (current_char == separators[i]) {
				is_separator = true;
				break;
			}
		}

		if (is_separator) {
			break;
		}

		data[size++] = current_char;
	}

	data[size] = '\0';

	return data;
}

string_t read_string(int max_size, FILE *stream)
{
	return generic_read_string(max_size, stream, " \n");
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


