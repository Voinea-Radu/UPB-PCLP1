/**
 * Converteste un numar din baza 8 in baza 10.
 * @param base8 Numarul in baza 8.
 * @return Numarul in baza 10.
 */
unsigned long convert_base8_to_base10(unsigned long base8);

/**
 * Calculeaza produsul scalar dintre 2 vectori, coordonata cu coordonata.
 * @param coord_v1 Coordonata primul vector
 * @param coord_v2 Coordonata celui de al doilea vector
 * @return Produsul scalar curent
 */
unsigned long long compute_scalar_product(unsigned long coord_v1,
										  unsigned long coord_v2);

/**
 * Calculeaza al doilea maxim dintre 2 vectori, coordonata cu coordonata.
 * @param coord_v1 Coordonata primul vector
 * @param coord_v2 Coordonata celui de al doilea vector
 * @param second_max_v1 Variabila de iesire a celui de al doilea maxim curent
 * @param second_max_v2 Variabila de iesire a celui de al doilea maxim curent
 */
void compute_second_maximum(unsigned long coord_v1, unsigned long coord_v2,
							long long *second_max_v1,
							long long *second_max_v2);

/**
 * Calculeaza norma vectorilor, coordonata cu coordonata.
 * @param coord_v1 Coordonata primul vector
 * @param coord_v2 Coordonata celui de al doilea vector
 * @param norma_v1 Variabila de iesire a normei primului vectorm
 * @param norma_v2 Variabila de iesire a normei celui de al doilea vector
 */
void compute_norm(unsigned long coord_v1, unsigned long coord_v2,
				  double *norma_v1, double *norma_v2);

// TODO - Maybe make compute_second_maximum and compute_norm for only one vector
