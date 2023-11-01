#include <stdio.h>
#include <malloc.h>
#include "board_utils.h"
#include "utils.h"

int main(void)
{
	int baord_size = 0;

	// Citire numar de linii si coloane
	scanf("%d", &baord_size);

	int **board = read_int_matrix(baord_size, baord_size);

	// Procesare tablei
	result res = process_board(baord_size, board, 0, 0);

	// Convertire coordonata x la litera
	char literal_coordinate[2];
	convert_coord_to_literal(res.x, literal_coordinate);

	// Afisare rezultate
	printf("%d\n%d %s", res.distance, res.y, literal_coordinate);

	// Eliberare memorie
	free(board);
	return 0;
}
