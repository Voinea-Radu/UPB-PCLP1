/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STATE_MANAGER_H
#define TEMA3_STATE_MANAGER_H

#include "string_utils.h"
#include "image.h"

// Handle function exit codes
#define EXIT 0
#define CONTINUE 1
#define UNKNOWN_COMMAND 2

// Other defines
#define MAX_ARGUMENT_SIZE 100


typedef struct{
	string_t key;

	int (*handle)(image_t *);
} string_to_handle;

int process_command(string_t command);

int handle_load(image_t *image);

int handle_print(image_t *image);

int handle_exit(image_t *image);
int handle_select(image_t *image);

#endif //TEMA3_STATE_MANAGER_H
