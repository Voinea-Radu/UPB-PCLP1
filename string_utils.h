/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STRING_UTILS_H
#define TEMA3_STRING_UTILS_H

#include <malloc.h>

typedef char *string_t;

string_t read_string(int max_size, FILE *stream);

string_t read_line(int max_size, FILE *stream);

void reset_buffer(string_t buffer, size_t *buffer_index);

string_t *split_string(int *size, string_t string, char separator);

void to_lower(string_t string);

void to_upper(string_t string);


#endif //TEMA3_STRING_UTILS_H
