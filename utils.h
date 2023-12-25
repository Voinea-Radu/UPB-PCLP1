/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_UTILS_H
#define TEMA3_UTILS_H

#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bits/stdint-uintn.h>

#include "string_utils.h"

// Math macros
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// Math utils

bool is_power_of_two(uint32_t number);

int clamp(int value, int min, int max);

// Memory utils
void *safe_malloc(size_t size);

void *safe_realloc(void *ptr, size_t size);

void *safe_calloc(size_t size);

#endif //TEMA3_UTILS_H

