#include <stdio.h>
#include "points_utils.h"

int main(void)
{
	// Citire numar de materii
	int number_of_courses = 0;
	int minim_points = 0;

	scanf("%d", &number_of_courses);

	int grades[number_of_courses];
	int credits[number_of_courses];

	// Citire grades
	for (int i = 0; i < number_of_courses; i++)
		scanf("%d", &grades[i]);

	// Citire credits
	for (int i = 0; i < number_of_courses; i++)
		scanf("%d", &credits[i]);

	// Citire current_points minim
	scanf("%d", &minim_points);

	// Calculare current_points curent
	int current_points = compute_points
			(number_of_courses, grades, credits);

	// Calculare numar minim de materii	pentru a ajunge la punctajul minim
	int minimum_courses = compute_minimum_courses
			(current_points, minim_points,
			 number_of_courses, grades, credits);

	// Afisarea numarului minim de materii pentru a ajunge la punctajul minim
	printf("%d\n", minimum_courses);

	return 0;
}

