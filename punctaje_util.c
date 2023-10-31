#include "punctaje_util.h"

int calcul_punctaj(int numar_materii, const int *note, const int *credite)
{
	int punctaj = 0;

	// Calculam punctajul pentru fiecare materie prin formula: nota * credite
	for (int i = 0; i < numar_materii; i++)
		punctaj += note[i] * credite[i];

	return punctaj;
}

int calcul_minim_materii(int punctaj, int punctaj_minim, int numar_materii,
						 int *note, const int *credite)
{
	if (punctaj >= punctaj_minim)
		return 0;

	int max = 0;
	int max_index = 0;

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

	// Adaugam delta-ul de punctaj la punctajul curent
	punctaj += max;
	// Marcam nota ca fiind 10
	note[max_index] = 10;

	// Apelam recursiv functia pentru a calcula numarul minim de materii
	return 1 + calcul_minim_materii
			(punctaj, punctaj_minim, numar_materii, note, credite);
}

