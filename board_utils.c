#include <stdlib.h>

#include "board_utils.h"

result process_board(int board_size, int **board, int x, int y)
{
	static long long distance;
	int cell = board[y][x];

	// Am ajuns la o celulta deja vizitata sau marcata ca cell de iesire (0)
	if (cell == 0) {
		result _result;
		_result.distance = distance;
		_result.x = x;
		_result.y = board_size - y;
		return _result;
	}

	// Adaugam distance parcursa si marcam casuta ca vizitata
	distance += abs(cell);
	board[y][x] = 0;

	if (is_white(x, y)) {
		// Deplasare pe linie
		x += cell;
		x %= board_size;
		if (x < 0)
			x += board_size;
	} else {
		// Deplasare pe coloana
		y += cell;
		y %= board_size;
		if (y < 0)
			y += board_size;
	}

	return process_board(board_size, board, x, y);
}

int is_white(int x, int y)
{
	return (x + y) % 2 == 0;
}

void convert_coord_to_literal(int n, char *output)
{
	int div_result = n / 26;
	int mod_result = n % 26;

	if (div_result > 0) {
		// Convertim cu doar o litera in cazul in care numarul este mai mare
		// decat 26
		output[0] = 'A' + div_result - 1;
		output[1] = 'A' + mod_result;
	} else {
		// Convertim cu doar o litera in cazul in care numarul este mai mic
		// decat 26
		output[0] = 'A' + mod_result;
	}
}
