/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STRING_UTILS_H
#define TEMA3_STRING_UTILS_H

#include <malloc.h>

typedef char* t_string;

t_string read_string(int max_size, FILE *stream);

t_string read_line(int max_size, FILE *stream);

t_string* split_string(t_string string, char* separator, int *size);

void *safe_malloc(size_t size);

#endif //TEMA3_STRING_UTILS_H
