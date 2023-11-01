#include <stdio.h>
#include "math_utils.h"

int main(void)
{
	// Citirea numarului de coordonate
	unsigned long number_of_coordinates = 0;
	scanf("%lu", &number_of_coordinates);

	// Variabile pentru calculul produsului scalar
	unsigned long long scalar_product = 0;

	// Variabile pentru calculul celui de al 2-lea maxim
	unsigned long second_maxim[2] = {0};

	// Variabile pentru calculul normei vectorilor
	double norm[2] = {0};

	for (unsigned long coord_index = 0; coord_index < number_of_coordinates;
		 coord_index++) {
		unsigned long coordinates[2] = {0};

		for (unsigned long vector_index = 0; vector_index < 2; vector_index++) {
			// Citim coordonatele vectorilor in baza 8
			unsigned long tmp_b8 = 0;
			scanf("%lu", &tmp_b8);

			// Convertim si salvam coordonata in baza 10
			coordinates[vector_index] = convert_base8_to_base10(tmp_b8);

			// Al 2-lea maxim
			second_maxim[vector_index] = compute_second_maximum
					(vector_index, coordinates[vector_index]);

			// Norma
			norm[vector_index] = compute_norm
					(vector_index, coordinates[vector_index]);
		}

		// Produs scalar
		scalar_product = compute_scalar_product
				(2, coordinates);
	}

	// Afisare produs scalar
	printf("%llu\n", scalar_product);

	// Afisare al 2-lea maxim
	for (unsigned long vector_index = 0; vector_index < 2; vector_index++)
		printf("%lu ", second_maxim[vector_index]);
	printf("\n");

	// Afisare norm
	for (unsigned long vector_index = 0; vector_index < 2; vector_index++)
		printf("%.7f ", norm[vector_index]);
	printf("\n");

	return 0;
}

