#include "points_utils.h"

int compute_points(int numar_materii, const int *note, const int *credite)
{
	int punctaj = 0;

	// Calculam punctajul pentru fiecare materie prin formula: nota * credite
	for (int i = 0; i < numar_materii; i++)
		punctaj += note[i] * credite[i];

	return punctaj;
}

int compute_minimum_courses(int punctaj, int punctaj_minim, int numar_materii,
							int *note, const int *credite)
{
	if (punctaj >= punctaj_minim)
		return 0;

	int max = 0;
	int max_index = -1;

	// Cautam materia cu cel mai mare delta de punctaj posibil
	for (int i = 0; i < numar_materii; i++) {
		int punctaj_curent = note[i] * credite[i];
		int punctaj_posibil = 10 * credite[i];

		int delta_punctaj = punctaj_posibil - punctaj_curent;

		if (delta_punctaj > max) {
			max_index = i;
			max = delta_punctaj;
		}
	}

	if (max_index == -1)
		return -1;

	// Adaugam delta-ul de punctaj la punctajul curent
	punctaj += max;
	// Marcam nota ca fiind 10
	note[max_index] = 10;

	// Apelam recursiv functia pentru a calcula numarul minim de materii
	int result = compute_minimum_courses
			(punctaj, punctaj_minim, numar_materii, note, credite);

	if (result == -1)
		return -1;

	return result + 1;
}
