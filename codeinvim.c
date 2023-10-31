#include <stdio.h>
#include "punctaje_util.h"

int main(void)
{
	// Citire numar de materii
	int n = 0;
	int punctaj_minim = 0;

	scanf("%d", &n);

	int note[n];
	int credite[n];

	// Citire note
	for (int i = 0; i < n; i++)
		scanf("%d", &note[i]);

	// Citire credite
	for (int i = 0; i < n; i++)
		scanf("%d", &credite[i]);

	// Citire punctaj minim
	scanf("%d", &punctaj_minim);

	// Calculare punctaj curent
	int punctaj = calcul_punctaj(n, note, credite);

	// Calculare numar minim de materii	pentru a ajunge la punctajul minim
	int minim_materii = calcul_minim_materii
			(punctaj, punctaj_minim, n, note, credite);

	// Afisarea numarului minim de materii pentru a ajunge la punctajul minim
	printf("%d\n", minim_materii);

	return 0;
}

