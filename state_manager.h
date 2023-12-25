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
#define UNKNOWN_COMMAND 3

// Other defines
#define MAX_ARGUMENT_SIZE 100


typedef struct{
	string_t key;

	int (*handle)(string_t* args, int args_size,image_t *);
} string_to_handle;

void process_instruction(string_t instruction);
int process_command( string_t instruction);

int handle_load(string_t* args, int args_size,image_t *image);
int handle_print(string_t* args, int args_size, image_t *image);
int handle_convert_to_mono(string_t* args, int args_size, image_t *image);
int handle_save( string_t* args, int args_size,image_t *image);
int handle_exit( string_t* args, int args_size,image_t *image);
int handle_select(string_t* args, int args_size, image_t *image);
int handle_histogram( string_t* args, int args_size,image_t *image);
int handle_equalize(string_t* args, int args_size, image_t *image);
int handle_rotate(string_t* args, int args_size, image_t *image);
int handle_crop( string_t* args, int args_size,image_t *image);
int handle_apply(string_t* args, int args_size, image_t *image);
int handle_debug(string_t* args, int args_size, image_t *image);

#endif //TEMA3_STATE_MANAGER_H
