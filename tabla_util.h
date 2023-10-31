typedef struct {
	int x;
	int y;
	int distanta;
} rezultat;

/**
 * Returneaza rezultatul continand coordonatele de oprire si distanta parcursa
 * @param marime_tabla Marimea tablei
 * @param tabla matricea tablei
 * @param x pozitia curenta pe linie
 * @param y pozitia curenta pe coloana
 * @return rezultatul
 */
rezultat procesare_tabla(int marime_tabla, int **tabla, int x, int y);
/**
 * Verifica daca o celula este alba
 * @param x Pozitia pe linie
 * @param y Poziita pe coloana
 * @return Daca este alba sau nu
 */
int este_alb(int x, int y);
/**
 * Converteste un numar in coordonata de litera ( 0 -> A, 1 -> B, 2 -> C, ...)
 * @param n Numarul de convertit
 * @param output Sirul de caractere de iesire
 */
void converteste_la_litera(int n, char *output);
