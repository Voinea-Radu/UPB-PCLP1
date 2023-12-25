/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include "instructions.h"
#include "utils.h"

string_t get_next_instruction(instructions_t *instructions)
{
	if (instructions->cursor >= instructions->size) {
		instructions->cursor++;
		return NULL;
	}
	string_t output =  instructions->instructions[instructions->cursor++];

	return output;
}

void add_instruction(instructions_t *instructions, string_t instruction)
{
	if (instruction == NULL || strcmp(instruction, " ") == 0 || strcmp(instruction, "\n") == 0 ||
		strcmp(instruction, "") == 0) {
		return;
	}

	//instructions->instructions = safe_realloc(instructions->instructions,(instructions->size) *sizeof(string_t));
	instructions->instructions[instructions->size++] = instruction;
}

instructions_t init_instructions()
{
	instructions_t instructions;
	instructions.instructions = safe_malloc(1000 * sizeof(string_t));
	instructions.size = 0;
	instructions.cursor = 0;
	return instructions;
}

void move_cursor(instructions_t* instructions, uint32_t offset)
{
	instructions->cursor += offset;
}

void free_instructions(instructions_t instructions)
{
	for (size_t i = 0; i < instructions.size; i++) {
		free(instructions.instructions[i]);
	}
	free(instructions.instructions);
}