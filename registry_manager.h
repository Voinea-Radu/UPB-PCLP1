//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

typedef struct{
	double **matrix;
	unsigned int rows_count;
	unsigned int columns_count;
} MatrixRegistry;

MatrixRegistry *read_matrix_registry();
void print_matrix(MatrixRegistry *registry);
