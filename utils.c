/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include "utils.h"


void *safe_malloc(size_t size)
{
	void *result = malloc(size);

	if (result == NULL) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}

void *safe_calloc(size_t size)
{
	void *result = calloc(size, 1);

	if (result == NULL) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}

void *safe_realloc(void *ptr, size_t size)
{
	void *result = realloc(ptr, size);

	if (result == NULL) {
		printf("There was an error while allocating memory!\nExiting...\n");
		exit(1);
	}

	return result;
}
