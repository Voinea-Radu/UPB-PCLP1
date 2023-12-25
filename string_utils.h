/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STRING_UTILS_H
#define TEMA3_STRING_UTILS_H

#include <malloc.h>

typedef char* string_t;

string_t read_string(int max_size, FILE *stream);

void reset_buffer(string_t buffer, size_t *buffer_index);

void to_lower(string_t string);


#endif //TEMA3_STRING_UTILS_H
