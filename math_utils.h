/**
 * Converteste un numar din baza 8 in baza 10.
 * @param base8 Numarul in baza 8.
 * @return Numarul in baza 10.
 */
unsigned long convert_base8_to_base10(unsigned long base8);

/**
 * Calculeaza produsul scalar a number_of_coordinates vectori
 * @param number_of_coordinates Numarul de coordinates (implicit numarul de
 * vectori)
 * @param coordinates array-ul cu coordonatele vectorilor
 * @return
 */
unsigned long long compute_scalar_product(unsigned long number_of_coordinates,
										  const unsigned long *coordinates);

/**
 * Calculeaza al doilea maxim dintr-un vector.
 * @param vector_index Indexul vectorului
 * @param coord Coordonata vectorului de la indexul vector_index
 * @return Al doilea maxim din vectorul de la indexul vector_index.
 */
unsigned long compute_second_maximum(unsigned long vector_index,
									 unsigned long coord);

/**
 * Calculeaza norma vectorului de la indexul vector_index.
 * @param vector_index Indexul vectorului
 * @param coord Coordonata vectorului de la indexul vector_index
 * @return Norma vectorului de la indexul vector_index.
 */
double compute_norm(unsigned long vector_index, unsigned long coord);
