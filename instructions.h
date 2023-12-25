/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#ifndef TEMA3_INSTRUCTIONS_H
#define TEMA3_INSTRUCTIONS_H

#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bits/stdint-uintn.h>

#include "string_utils.h"

typedef struct instructions_t_prototype instructions_t;

struct instructions_t_prototype{
	string_t* instructions;
	uint32_t size;
	uint32_t cursor;
};

string_t get_next_instruction(instructions_t* instructions);

void add_instruction(instructions_t* instructions, string_t instruction);

instructions_t init_instructions();

void move_cursor(instructions_t* instructions, uint32_t offset);

void free_instructions(instructions_t instructions);

#endif //TEMA3_INSTRUCTIONS_H
