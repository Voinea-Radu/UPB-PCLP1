//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

typedef struct{
	double **matrix;
	unsigned int rows_count;
	unsigned int columns_count;
} MatrixRegistry;

MatrixRegistry *read_matrix_registry(int rows_count, int columns_count);
void print_matrix(MatrixRegistry *registry);
MatrixRegistry *create_from(MatrixRegistry *registry, int new_rows_count, const int *new_rows,
							int new_columns_count, const int *new_columns);
MatrixRegistry *multiply(MatrixRegistry *registry1, MatrixRegistry *registry2);
int compare(MatrixRegistry *registry1, MatrixRegistry *registry2);
MatrixRegistry* transpose(MatrixRegistry *registry);