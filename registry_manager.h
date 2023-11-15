//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#define MOD 10007

typedef struct{
	int **data;
	unsigned int rows_count;
	unsigned int columns_count;
} Matrix;

typedef struct{
	Matrix *matrices;
	unsigned int size;
	unsigned int capacity;
} MatrixRegistry;

Matrix *read_matrix_registry(int rows_count, int columns_count);

void print_matrix(Matrix *matrix);

Matrix *create_from(Matrix *matrix, unsigned int new_rows_count, const  unsigned int *new_rows,
					unsigned int new_columns_count, const unsigned int *new_columns);

Matrix *multiply(Matrix *matrix1, Matrix *matrix2);

int compare(Matrix *matrix1, Matrix *matrix2);

Matrix *transpose(Matrix *matrix);

Matrix *raise_to_power(Matrix *matrix, int power);

Matrix *multiply_strassen(Matrix *matrix1, Matrix *matrix2);

Matrix *sum_matrix(Matrix *matrix1, Matrix *matrix2);
Matrix * substract_matrix(Matrix *matrix1, Matrix *matrix2);