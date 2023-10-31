#include <math.h>
#include "math_util.h"

unsigned long convert_baza8_in_baza10(unsigned long baza_8)
{
	unsigned long baza_10 = 0;
	unsigned long putere = 1;

	while (baza_8 != 0) {
		unsigned long ultima_cifra = baza_8 % 10;
		baza_10 += ultima_cifra * putere;
		putere *= 8;
		baza_8 /= 10;
	}

	return baza_10;
}

unsigned long long calcul_produs_scalar(unsigned long numar_coordonate,
										const unsigned long *coordonate)
{
	static unsigned long long produs_scalar = 1;

	unsigned long long produs = 1;

	for (unsigned long i = 0; i < numar_coordonate; i++)
		produs *= coordonate[i];

	produs_scalar += produs;

	return produs_scalar;
}

unsigned long calcul_al_doilea_maxim(unsigned long vector_index,
									 unsigned long coord)
{
	static unsigned long max_1[2] = {0, 0};
	static unsigned long max_2[2] = {0, 0};

	if (max_1[vector_index] < coord) {
		max_2[vector_index] = max_1[vector_index];
		max_1[vector_index] = coord;
	}

	return max_2[vector_index];
}

double calcul_norma(unsigned long vector_index, unsigned long coord)
{
	static double norma[2] = {0, 0};

	norma[vector_index] += coord * coord;

	return sqrt(norma[vector_index]);
}

