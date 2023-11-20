//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <stdio.h>
#include "state_manager.h"

int main(void)
{
	char c = '0';

	do {
		scanf("%c", &c);

		// Daca c este un caracter de whitespace sau new line, il ignoram
		if (c == 10 || c == ' ')
			continue;

		// Daca c este o cifra, il ignoram
		if (c >= '0' && c <= '9')
			continue;

		handle_state(c);
	} while (c != 'Q');
}
