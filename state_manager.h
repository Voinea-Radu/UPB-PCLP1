/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STATE_MANAGER_H
#define TEMA3_STATE_MANAGER_H

#include "string_utils.h"
#include "image.h"

#define EXIT 0
#define CONTINUE 1

typedef struct { char *key; int value; } string_pair;

int process_command(string_t command);

void handle_load(image_t *image);

#endif //TEMA3_STATE_MANAGER_H
