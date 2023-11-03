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
	long long second_maxim_v1 = -1;
	long long second_maxim_v2 = -1;

	// Variabile pentru calculul normei vectorilor
	double norma_v1 = 0;
	double norma_v2 = 0;

	for (unsigned long index = 0; index < number_of_coordinates; index++) {
		unsigned long coordinate_v1_b8 = 0;
		unsigned long coordinate_v2_b8 = 0;

		scanf("%lu", &coordinate_v1_b8);
		scanf("%lu", &coordinate_v2_b8);

		unsigned long coordinate_v1 = convert_base8_to_base10(coordinate_v1_b8);
		unsigned long coordinate_v2 = convert_base8_to_base10(coordinate_v2_b8);

		// Produs scalar
		scalar_product = compute_scalar_product(coordinate_v1,
												coordinate_v2);

		// Al doilea maxim
		compute_second_maximum(coordinate_v1, coordinate_v2,
							   &second_maxim_v1,
							   &second_maxim_v2);

		// Norma
		compute_norm(coordinate_v1, coordinate_v2,
					 &norma_v1, &norma_v2);
	}

	// Afisare produs scalar
	printf("%llu\n", scalar_product);

	// Afisare al 2-lea maxim
	printf("%lld %lld\n", second_maxim_v1, second_maxim_v2);

	// Afisare norm
	printf("%.7f %.7f\n", norma_v1, norma_v2);

	return 0;
}

