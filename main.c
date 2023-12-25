/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <stdio.h>
#include <string.h>
#include "string_utils.h"
#include "state_manager.h"
#include "image.h"
#include "utils.h"

#define MAX_COMMAND_SIZE 100

int main(void)
{
	string_t instruction;

	while (1) {
		instruction = read_line(MAX_COMMAND_SIZE, stdin);

		if(instruction == NULL){
			break;
		}

		to_lower(instruction);

		int result = process_command(instruction);
		free(instruction);

		if(result == EXIT){
			break;
		}
	}

}
