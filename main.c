/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <stdio.h>
#include <unistd.h>
#include "string_utils.h"
#include "state_manager.h"
#include "image.h"

#define MAX_COMMAND_SIZE 100

int main(void)
{
	t_pixel pixel = new_pixel_color(50, 100, 150);

	t_string s;
	split_string(s,'a',NULL);

	printf("%d %d %d\n", pixel.rgb.red, pixel.rgb.green, pixel.rgb.blue);

	while (1) {
		t_string command = read_string(MAX_COMMAND_SIZE, stdin);
		process_command(command);
	}
}
