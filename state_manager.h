/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STATE_MANAGER_H
#define TEMA3_STATE_MANAGER_H

#include "string_utils.h"
#include "image.h"
#include "instructions.h"

// Handle function exit codes
#define EXIT 0
#define CONTINUE 1
#define UNKNOWN_COMMAND 3

// Other defines
#define MAX_ARGUMENT_SIZE 100


typedef struct{
	string_t key;

	int (*handle)(instructions_t* instructions, image_t *);
} string_to_handle;

void process_instructions(instructions_t instructions);
int process_command(instructions_t* instructions, string_t command, image_t *image);

int handle_load(instructions_t* instructions,image_t *image);
int handle_print(instructions_t* instructions, image_t *image);
int handle_convert_to_mono(instructions_t* instructions, image_t *image);
int handle_save(instructions_t* instructions, image_t *image);
int handle_exit(instructions_t* instructions, image_t *image);
int handle_select(instructions_t* instructions, image_t *image);
int handle_histogram(instructions_t* instructions, image_t *image);
int handle_equalize(instructions_t* instructions, image_t *image);
int handle_rotate(instructions_t* instructions, image_t *image);
int handle_crop(instructions_t* instructions, image_t *image);
int handle_apply(instructions_t* instructions, image_t *image);
int handle_debug(instructions_t* instructions, image_t *image);

#endif //TEMA3_STATE_MANAGER_H
