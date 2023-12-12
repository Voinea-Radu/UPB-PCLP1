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

void tests(); // TODO Remove this function

int main(void)
{
	//tests();

	while (1) {
		string_t command = read_string(MAX_COMMAND_SIZE, stdin);
		process_command(command);
	}
}

// TODO Remove this function
void tests(){
	pixel_t pixel = new_pixel_color(50, 100, 150);

	size_t size = 0;
	string_t *split = split_string("This is just a test string"," ",&size);

	printf("==============================\n");
	printf("==============================\n");

	printf("%lu\n", size);

	for (int i = 0; i < size; i++) {
		printf("%s\n", split[i]);
	}

	printf("==============================\n");
	printf("==============================\n");

	printf("%d %d %d\n", pixel.rgb.red, pixel.rgb.green, pixel.rgb.blue);
}
