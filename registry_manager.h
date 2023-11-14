//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

typedef struct{
	double **matrix;
	unsigned int rows_count;
	unsigned int columns_count;
} Matrix;

typedef struct{
	Matrix *matrices;
	unsigned int size;
	unsigned int capacity;
} MatrixRegistry;

Matrix *read_matrix_registry(int rows_count, int columns_count);

void print_matrix(Matrix *registry);

Matrix *create_from(Matrix *registry, int new_rows_count, const int *new_rows,
					int new_columns_count, const int *new_columns);

Matrix *multiply(Matrix *registry1, Matrix *registry2);

int compare(Matrix *registry1, Matrix *registry2);

Matrix *transpose(Matrix *registry);

Matrix *raise_to_power(Matrix *registry, int power);