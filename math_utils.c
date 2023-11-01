#include <math.h>
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

unsigned long long compute_scalar_product(unsigned long number_of_coordinates,
										  const unsigned long *coordinates)
{
	static unsigned long long scalar_product = 1;

	unsigned long long tmp_product = 1;

	for (unsigned long i = 0; i < number_of_coordinates; i++)
		tmp_product *= coordinates[i];

	scalar_product += tmp_product;

	return scalar_product;
}

unsigned long compute_second_maximum(unsigned long vector_index,
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

double compute_norm(unsigned long vector_index, unsigned long coord)
{
	static double norma[2] = {0, 0};

	norma[vector_index] += coord * coord;

	return sqrt(norma[vector_index]);
}
