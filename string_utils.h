/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STRING_UTILS_H
#define TEMA3_STRING_UTILS_H

#include <malloc.h>

typedef char* string_t;

string_t read_string(int max_size, FILE *stream);

string_t read_line(int max_size, FILE *stream);

string_t* split_string(string_t data, string_t separator, size_t *size);

void reset_buffer(string_t *buffer, size_t *buffer_index);

#endif //TEMA3_STRING_UTILS_H
