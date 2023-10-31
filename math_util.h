/**
 * Converteste un numar din baza 8 in baza 10.
 * @param baza_8 Numarul in baza 8.
 * @return Numarul in baza 10.
 */
unsigned long convert_baza8_in_baza10(unsigned long baza_8);
/**
 * Calculeaza produsul scalar a numar_coordonate vectori
 * @param numar_coordonate Numarul de coordonate (implicit numarul de vectori)
 * @param coordonate array-ul cu coordonatele vectorilor
 * @return
 */
unsigned long long calcul_produs_scalar(unsigned long numar_coordonate,
										const unsigned long *coordonate);

/**
 * Calculeaza al doilea maxim dintr-un vector.
 * @param vector_index Indexul vectorului
 * @param coord Coordonata vectorului de la indexul vector_index
 * @return Al doilea maxim din vectorul de la indexul vector_index.
 */
unsigned long calcul_al_doilea_maxim(unsigned long vector_index,
									 unsigned long coord);
/**
 * Calculeaza norma vectorului de la indexul vector_index.
 * @param vector_index Indexul vectorului
 * @param coord Coordonata vectorului de la indexul vector_index
 * @return Norma vectorului de la indexul vector_index.
 */
double calcul_norma(unsigned long vector_index, unsigned long coord);
