typedef struct {
	int x;
	int y;
	int distance;
} result;

/**
 * Returneaza rezultatul continand coordonatele de oprire si distance parcursa
 * @param board_size Marimea tablei
 * @param board matricea tablei
 * @param x pozitia curenta pe linie
 * @param y pozitia curenta pe coloana
 * @return rezultatul
 */
result process_board(int board_size, int **board, int x, int y);
/**
 * Verifica daca o celula este alba
 * @param x Pozitia pe linie
 * @param y Poziita pe coloana
 * @return Daca este alba sau nu
 */
int is_white(int x, int y);
/**
 * Converteste un numar in coordonata de litera ( 0 -> A, 1 -> B, 2 -> C, ...)
 * @param n Numarul de convertit
 * @param output Sirul de caractere de iesire
 */
void convert_coord_to_literal(int n, char *output);
