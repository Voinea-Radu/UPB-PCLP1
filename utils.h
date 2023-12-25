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
#include <linux/types.h>
#include <bits/stdint-uintn.h>

#include "string_utils.h"

// Math macros

__u32 max(__u32 max_a, __u32 max_b)
{
	return max_a > max_b ? max_a : max_b;
}

__u32 min(__u32 min_a, __u32 min_b)
{
	return min_a < min_b ? min_a : min_b;
}

// Math utils

bool is_power_of_two(__u32 number);

int clamp(int value, int min, int max);

bool is_number(string_t string);

// Memory utils
void *safe_malloc(size_t size);

void *safe_realloc(void *ptr, size_t size);

void *safe_calloc(size_t size);

void free_matrix(void **matrix, size_t rows);

#endif //TEMA3_UTILS_H

