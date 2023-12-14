/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>

#ifndef TEMA3_UTILS_H
#define TEMA3_UTILS_H

// Math macros
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// Memory utils
void *safe_malloc(size_t size);

void *safe_realloc(void *ptr, size_t size);

void *safe_calloc(size_t size);

#endif //TEMA3_UTILS_H
