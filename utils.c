/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <ctype.h>
#include <string.h>
#include "utils.h"

void *safe_malloc(size_t size)
{
	void *result = malloc(size);

	if (0 == result) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}

void *safe_calloc(size_t size)
{
	void *result = calloc(size, 1);

	if (0 == result) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}

void *safe_realloc(void *ptr, size_t size)
{
	void *result = realloc(ptr, size);

	if (0 == result) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}

bool is_power_of_two(__u32 number)
{
	return (number & (number - 1)) == 0;
}

int clamp(int value, int min, int max)
{
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}

void free_matrix(void **matrix, size_t rows)
{
	for (size_t i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

bool is_number(string_t string)
{
	for (size_t i = 0; i < strlen(string); i++)
		if (!isdigit(string[i]) && string[i] != '-')
			return false;

	return true;
}
