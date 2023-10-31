#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <malloc.h>
#include "tabla_util.h"

int main(void)
{
	int n = 0;

	// Citire numar de linii si coloane
	scanf("%d", &n);

	int **tabla = malloc(n * sizeof(int *));

	// Citire tabla
	for (int i = 0; i < n; i++) {
		tabla[i] = malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
			scanf("%d", &tabla[i][j]);
	}

	// Procesare tablei
	rezultat rez = procesare_tabla(n, tabla, 0, 0);

	// Convertire coordonata x la litera
	char coordonata_literal[2];
	converteste_la_litera(rez.x, coordonata_literal);

	// Afisare rezultate
	printf("%d\n%d %s", rez.distanta, rez.y, coordonata_literal);

	// Eliberare memorie
	free(tabla);
	return 0;
}

