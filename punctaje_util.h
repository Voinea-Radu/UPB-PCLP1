/**
 * Calculeaza punctajul unui student
 * @param numar_materii Numarul de materii
 * @param note Array-ul cu notele asociate fiecarei materii
 * @param credite Array-ul cu creditele asociate fiecarei materii
 * @return Punctajul studentului
 */
int calcul_punctaj(int numar_materii, const int *note, const int *credite);

/**
 * Calculeaza numarul minim de materii la care trebuie obtinuta nota 10 pentru
 * a ajunge la punctajul minim
 * @param punctaj Punctajul curent
 * @param punctaj_minim Punctajul minim
 * @param numar_materii Numarul de materii
 * @param note Array-ul cu notele asociate fiecarei materii
 * @param credite Array-ul cu creditele asociate fiecarei materii
 * @return Numarul minim de materii
 */
int calcul_minim_materii(int punctaj, int punctaj_minim, int numar_materii,
						 int *note, const int *credite);
