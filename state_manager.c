//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <malloc.h>
#include "state_manager.h"

void handle_state(char state)
{
	static MatrixRegistry *registry = NULL;

	if (registry == NULL) {
		registry = malloc(sizeof(MatrixRegistry));
		registry->size = 0;
		registry->capacity = 1;
		registry->matrices = malloc(sizeof(Matrix));
	}

	switch (state) {
		case 'L':
			handle_read(registry);
			break;
		case 'D':
			handle_print_dimension(registry);
			break;
		case 'P':
			handle_print(registry);
			break;
		case 'C':
			handle_resize(registry);
			break;
		case 'M':
			handle_multiply(registry);
			break;
		case 'O':
			handle_sort(registry);
			break;
		case 'T':
			handle_transpose(registry);
			break;
		case 'R':
			handle_raise_to_power(registry);
			break;
		default:
			return;
	}
}

void handle_read(MatrixRegistry *registry)
{
	int rows_count, columns_count;

	scanf("%d %d", &rows_count, &columns_count);

	Matrix *matrix = read_matrix_registry(rows_count, columns_count);

	handle_save(registry, matrix);
}

void handle_save(MatrixRegistry *registry, Matrix *matrix)
{
	registry->size++;

	if (registry->size > registry->capacity) {
		registry->capacity *= 2;
		registry->matrices = realloc(registry->matrices, (sizeof(Matrix)) * registry->capacity);
	}

	handle_save_at(registry, registry->size - 1, matrix);
}

void handle_print_dimension(MatrixRegistry *registry)
{
	unsigned int index;
	scanf("%ud", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix = &registry->matrices[index];

	printf("%d %d\n", matrix->rows_count, matrix->columns_count);
}

void handle_print(MatrixRegistry *registry)
{
	unsigned int index;
	scanf("%ud", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix = &registry->matrices[index];

	print_matrix(matrix);
}

void handle_resize(MatrixRegistry *registry)
{
	unsigned int index, new_rows_count, new_columns_count;
	scanf("%ud", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	scanf("%ud", &new_rows_count);
	int *new_rows = malloc(sizeof(int) * new_rows_count);

	for (int i = 0; i < new_rows_count; i++) {
		scanf("%ud", &new_rows[i]);
	}

	scanf("%ud", &new_columns_count);
	int *new_columns = malloc(sizeof(int) * new_columns_count);

	for (int i = 0; i < new_columns_count; i++) {
		scanf("%ud", &new_columns[i]);
	}

	Matrix *matrix = &registry->matrices[index];

	Matrix *new_matrix = create_from(matrix, new_rows_count, new_rows,
									 new_columns_count, new_columns);

	handle_save_at(registry, index, new_matrix);
}

void handle_multiply(MatrixRegistry *registry)
{
	int index1, index2;
	scanf("%ud%ud", &index1, &index2);

	if (index1 >= registry->size || index2 >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix1 = &registry->matrices[index1];
	Matrix *matrix2 = &registry->matrices[index2];

	Matrix *matrix = multiply(matrix1, matrix2);

	if (matrix == NULL) {
		return;
	}

	handle_save(registry, matrix);
}

void handle_sort(MatrixRegistry *registry)
{
	for (int i = 0; i < registry->size; i++) {
		for (int j = i + 1; j < registry->size; j++) {
			if (compare(&registry->matrices[i], &registry->matrices[j]) == 1) {
				Matrix *aux = &registry->matrices[i];
				registry->matrices[i] = registry->matrices[j];
				registry->matrices[j] = *aux;
			}
		}
	}
}

void handle_transpose(MatrixRegistry *registry)
{
	unsigned int index;
	scanf("%ud", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix = &registry->matrices[index];
	Matrix *new_matrix = transpose(matrix);

	handle_save_at(registry, index, new_matrix);
}

void handle_save_at(MatrixRegistry *registry, unsigned int index, Matrix *matrix)
{
	registry->matrices[index] = *matrix;

	printf("Successfully saved the matrix to index %d\n", index); // TODO Delete
}

void handle_raise_to_power(MatrixRegistry *registry)
{
	unsigned int index;
	int power;
	scanf("%ud%d", &index, &power);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix = &registry->matrices[index];

	Matrix *new_matrix = raise_to_power(matrix, power);

	if (new_matrix == NULL) {
		return;
	}

	handle_save_at(registry	, index, new_matrix);
}