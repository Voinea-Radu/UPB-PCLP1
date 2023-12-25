/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <stdio.h>
#include <string.h>
#include "string_utils.h"
#include "state_manager.h"
#include "image.h"
#include "instructions.h"
#include "utils.h"

#define MAX_COMMAND_SIZE 100

int main(void)
{
	//tests();

	instructions_t instructions = init_instructions();
	string_t command;

	while (1) {
		command = read_string(MAX_COMMAND_SIZE, stdin);

		if(command == NULL){
			break;
		}

		to_lower(command);

		if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
			break;
		}

		add_instruction(&instructions, command);
	}

	free(command);

	process_instructions(instructions);

	free_instructions(instructions);
}
