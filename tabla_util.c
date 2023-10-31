#include "tabla_util.h"
#include <stdlib.h>

rezultat procesare_tabla(int marime_tabla, int **tabla, int x, int y)
{
	static int distanta;
	int celula = tabla[y][x];

	// Am ajuns la o celulta deja vizitata sau marcata ca celula de iesire (0)
	if (celula == 0) {
		rezultat r;
		r.distanta = distanta;
		r.x = x;
		r.y = marime_tabla - y;
		return r;
	}

	// Adaugam distanta parcursa si marcam casuta ca vizitata
	distanta += abs(celula);
	tabla[y][x] = 0;

	if (este_alb(x, y)) {
		// Deplasare pe linie
		x += celula;
		x %= marime_tabla;
		if (x < 0)
			x += marime_tabla;
	} else {
		// Deplasare pe coloana
		y += celula;
		y %= marime_tabla;
		if (y < 0)
			y += marime_tabla;
	}

	return procesare_tabla(marime_tabla, tabla, x, y);
}

int este_alb(int x, int y)
{
	return (x + y) % 2 == 0;
}

void converteste_la_litera(int n, char *output)
{
	int rezultat = n / 26;
	int rest = n % 26;

	if (rezultat > 0) {
		// Convertim cu doar o litera in cazul in care numarul este mai mare
		// decat 26
		output[0] = 'A' + rezultat - 1;
		output[1] = 'A' + rest;
	} else {
		// Convertim cu doar o litera in cazul in care numarul este mai mic
		// decat 26
		output[0] = 'A' + rest;
	}
}

