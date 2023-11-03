#include <stdio.h>
#include "points_utils.h"
#include "utils.h"

int main(void)
{
	// Citire numar de materii
	int number_of_courses = 0;
	int minim_points = 0;

	scanf("%d", &number_of_courses);

	int *grades = read_int_array(number_of_courses);
	int *credits = read_int_array(number_of_courses);

	// Citire current_points minim
	scanf("%d", &minim_points);

	// Calculare current_points curent
	int current_points = compute_points
			(number_of_courses, grades, credits);

	// Calculare numar minim de materii	pentru a ajunge la punctajul minim
	// Calculare numar minim de materii	pentru a ajunge la punctajul minim
	int minimum_courses = compute_minimum_courses
			(current_points, minim_points,
			 number_of_courses, grades, credits);

	// Afisarea numarului minim de materii pentru a ajunge la punctajul minim
	printf("%d\n", minimum_courses);

	return 0;
}

