// ********************************************
// Copyright Voinea Radu-Mihai 315CAa 2023-2024
// ********************************************

#define MOD 10007

/**
 * Structura care retine o matrice
 */
typedef struct{
	int **data;
	unsigned int rows_count;
	unsigned int columns_count;
} t_matrix;

/**
 * Structura care retine un registry de matrici
 */
typedef struct{
	t_matrix *matrices;
	unsigned int size;
	unsigned int capacity;
} t_matrix_registry;

/**
 * Citeste o matrice de la tastatura
 * @param rows_count    Numarul de linii al matricei
 * @param columns_count Numarul de coloane al matricei
 * @return
 */
t_matrix *read_matrix_registry(unsigned int rows_count,
							   unsigned int columns_count);

/**
 * Afiseaza dimensiunea unei matrice
 * @param matrix Matricea care se afiseaza
 */
void print_matrix(t_matrix *matrix);

/**
 * Creaza o noua matrice in o matrice existenta
 * @param matrix            Matricea care se afiseaza
 * @param new_rows_count    Numarul de linii al matricei
 * @param new_rows          Vectorul de linii al matricei
 * @param new_columns_count Numarul de coloane al matricei
 * @param new_columns       Vectorul de coloane al matricei
 * @return  			    Noua matrice
 */
t_matrix *create_from(t_matrix *matrix, unsigned int new_rows_count,
					  const unsigned int *new_rows,
					  unsigned int new_columns_count,
					  const unsigned int *new_columns);

/**
 * Multiplica 2 matrici
 * @param matrix1 Matricea 1 de multiplica
 * @param matrix2 Matricea 2 de multiplica
 * @return        Matricea rezultata
 */
t_matrix *multiply(t_matrix *matrix1, t_matrix *matrix2);

/**
 * Compara 2 matrici, prin insumarea elementelor si compararea sumelor
 * @param matrix1 Matricea 1 de comparat
 * @param matrix2 Matricea 2 de comparat
 * @return        1 daca sum(matrix1) > sum(matrix2), 0 altfel
 */
int compare(t_matrix *matrix1, t_matrix *matrix2);

/**
 * Transpune o matrice
 * @param matrix Matricea care se transpune
 * @return       Matricea transpusa
 */
t_matrix *transpose(t_matrix *matrix);

/**
 * Ridica o matrice la o putere
 * @param matrix Matricea care se ridica la putere
 * @param power  Puterea la care se ridica matricea
 * @return       Matricea rezultata
 */
t_matrix *raise_to_power(t_matrix *matrix, int power);

/**
 * Ridica o matrice la o putere folosind algoritmul Strassen
 * @param matrix1 Matricea 1 de multiplicat
 * @param matrix2 Matricea 2 de multiplicat
 * @return        Matricea rezultata
 */
t_matrix *multiply_strassen(t_matrix *matrix1, t_matrix *matrix2);

/**
 * Executa algoritmul Strassen
 * @param matrix1 Matricea 1 de multiplicat
 * @param matrix2 Matricea 2 de multiplicat
 * @param C1      Matricea intermediara 1
 * @param C2      Matricea intermediara 2
 * @param C3      Matricea intermediara 3
 * @param C4      Matricea intermediara 4
 * @return  	  Matricea rezultata
 */
t_matrix *exec_strassen(t_matrix *matrix1, t_matrix *matrix2,
						t_matrix *C1, t_matrix *C2, t_matrix *C3, t_matrix *C4
);

/**
 * Aduna 2 matrici
 * @param matrix1 Matricea 1 de adunat
 * @param matrix2 Matricea 2 de adunat
 * @return        Matricea rezultata
 */
t_matrix *sum_matrix(t_matrix *matrix1, t_matrix *matrix2);

/**
 * Scade 2 matrici
 * @param matrix1 Matricea 1 de scazut
 * @param matrix2 Matricea 2 de scazut
 * @return        Matricea rezultata
 */
t_matrix *substract_matrix(t_matrix *matrix1, t_matrix *matrix2);

/**
 * Returneaza numar % MOD. Iar daca rezultatul este negatic numar % MOD + MOD
 * @param number Numarul care se modifica
 * @return       Numarul modificat
 */
int mod(int number);
