//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#define MOD 10007

typedef struct{
	int **data;
	unsigned int rows_count;
	unsigned int columns_count;
} t_matrix;

typedef struct{
	t_matrix *matrices;
	unsigned int size;
	unsigned int capacity;
} t_matrix_registry;

t_matrix *read_matrix_registry(unsigned int rows_count,
							   unsigned int columns_count);

void print_matrix(t_matrix *matrix);

t_matrix *create_from(t_matrix *matrix, unsigned int new_rows_count,
					  const unsigned int *new_rows,
					  unsigned int new_columns_count,
					  const unsigned int *new_columns);

t_matrix *multiply(t_matrix *matrix1, t_matrix *matrix2);

int compare(t_matrix *matrix1, t_matrix *matrix2);

t_matrix *transpose(t_matrix *matrix);

t_matrix *raise_to_power(t_matrix *matrix, int power);

t_matrix *multiply_strassen(t_matrix *matrix1, t_matrix *matrix2);

t_matrix *exec_strassen(t_matrix *matrix1, t_matrix *matrix2,
						t_matrix *C1, t_matrix *C2, t_matrix *C3, t_matrix *C4
);

t_matrix *sum_matrix(t_matrix *matrix1, t_matrix *matrix2);

t_matrix *substract_matrix(t_matrix *matrix1, t_matrix *matrix2);

int mod(int number);
