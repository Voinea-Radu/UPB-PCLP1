#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include "math_util.h"

int main(void)
{
	// Citirea numarului de coordonate
	unsigned long n = 0;
	scanf("%lu", &n);

	// Variabile pentru calculul produsului scalar
	unsigned long long produs_scalar = 0;

	// Variabile pentru calculul celui de al 2-lea maxim
	unsigned long maxime_secunde[2] = {0};

	// Variabile pentru calculul normei vectorilor
	double norma[2] = {0};

	for (unsigned long coord_index = 0; coord_index < n; coord_index++) {
		unsigned long coordonate[2] = {0};

		for (unsigned long vector_index = 0; vector_index < 2; vector_index++) {
			// Citim coordonatele vectorilor in baza 8
			unsigned long tmp_b8 = 0;
			scanf("%lu", &tmp_b8);

			// Convertim si salvam coordonata in baza 10
			coordonate[vector_index] = convert_baza8_in_baza10(tmp_b8);

			// Al 2-lea maxim
			maxime_secunde[vector_index] = calcul_al_doilea_maxim
					(vector_index, coordonate[vector_index]);

			// Norma
			norma[vector_index] = calcul_norma
					(vector_index, coordonate[vector_index]);
		}

		// Produs scalar
		produs_scalar = calcul_produs_scalar(2, coordonate);
	}

	// Afisare produs scalar
	printf("%llu\n", produs_scalar);

	// Afisare al 2-lea maxim
	for (unsigned long vector_index = 0; vector_index < 2; vector_index++)
		printf("%lu ", maxime_secunde[vector_index]);
	printf("\n");

	// Afisare norma
	for (unsigned long vector_index = 0; vector_index < 2; vector_index++)
		printf("%.7f ", norma[vector_index]);
	printf("\n");

	return 0;
}

