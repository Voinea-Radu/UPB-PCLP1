//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <stdio.h>
#include "state_manager.h"

int main(void){

	char c = '0';

	while (c != 'S'){
		printf("> "); // TODO Delete
		scanf("%s", &c);

		handle_state(c);
	}
}