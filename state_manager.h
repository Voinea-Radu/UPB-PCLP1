/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_STATE_MANAGER_H
#define TEMA3_STATE_MANAGER_H

#include "string_utils.h"
#include "image.h"

typedef struct { char *key; int value; } string_pair;

void process_command(t_string command);

void handle_load(t_image *image);

#endif //TEMA3_STATE_MANAGER_H
