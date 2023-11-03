#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include "math_utils.h"

unsigned long convert_base8_to_base10(unsigned long base8)
{
	unsigned long base10 = 0;
	unsigned long power = 1;

	while (base8 != 0) {
		unsigned long last_digit = base8 % 10;
		base10 += last_digit * power;
		power *= 8;
		base8 /= 10;
	}

	return base10;
}

unsigned long long compute_scalar_product(unsigned long coord_v1,
										  unsigned long coord_v2)
{
	static unsigned long long scalar_product;

	scalar_product += (coord_v1 * coord_v2);

	return scalar_product;
}

void compute_second_maximum(unsigned long coord_v1, unsigned long coord_v2,
							long long *second_max_v1_out,
							long long *second_max_v2_out)
{
	static long long first_max[2] = {-1, -1};
	static long long second_max[2] = {-1, -1};

	long long coordinates[2] = {coord_v1, coord_v2};

	// Iteram pentru vectorul creat pentru a evita copierea codului
	for (int index = 0; index < 2; index++) {
		// Cazul in care nu a fost setat un maxim inca
		if (first_max[index] == -1) {
			first_max[index] = coordinates[index];
		} else {
			// Cazul in care un maxim a fost setat iar un al doilea maxim nu a
			// fost setat inca
			if (second_max[index] == -1) {
				// Veriricam care dintre daca noua valoare este mai mare sau
				// mai mica decat first maxim, data este egala cu maximul
				// ignoram
				if (coordinates[index] < first_max[index]) {
					second_max[index] = coordinates[index];
				} else if (coordinates[index] > first_max[index]) {
					second_max[index] = first_max[index];
					first_max[index] = coordinates[index];
				}
			} else {
				// Cazul in care si maximul si al doilea maxim au fost setate
				// Verificam daca noul numar este un nou maxim
				if (coordinates[index] > first_max[index]) {
					second_max[index] = first_max[index];
					first_max[index] = coordinates[index];
				} else if (coordinates[index] > second_max[index] &&
						   coordinates[index] != first_max[index]) {
					// Cazul in care noul numar nu este mai mare decat maximul
					// dar este diferit de acesta si in celasi timp mai mare
					// decat cel de al doilea maxim
					second_max[index] = coordinates[index];
				}
			}
		}
	}

	*second_max_v1_out = second_max[0];
	*second_max_v2_out = second_max[1];
}

void compute_norm(unsigned long coord_v1, unsigned long coord_v2,
				  double *norma_v1, double *norma_v2)
{
	static double norma_pow2_v1;
	static double norma_pow2_v2;

	norma_pow2_v1 += coord_v1 * coord_v1;
	norma_pow2_v2 += coord_v2 * coord_v2;

	*norma_v1 = sqrt(norma_pow2_v1);
	*norma_v2 = sqrt(norma_pow2_v2);
}
