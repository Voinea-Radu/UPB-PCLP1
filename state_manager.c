//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <malloc.h>
#include "state_manager.h"

void handle_load_matrix(int *size, MatrixRegistry **memory);

void handle_print_matrix_dimension(const int *size, MatrixRegistry **memory);

void handle_print_matrix(const int *size, MatrixRegistry **memory);

void handle_resize_matrix(const int *size, MatrixRegistry **memory);

void handle_state(char state)
{
	static int matrix_memory_size = 0;
	static MatrixRegistry *matrix_memory;

	switch (state) {
		case 'L':
			handle_load_matrix(&matrix_memory_size, &matrix_memory);
			break;
		case 'D':
			handle_print_matrix_dimension(&matrix_memory_size, &matrix_memory);
			break;
		case 'P':
			handle_print_matrix(&matrix_memory_size, &matrix_memory);
			break;
		case 'C':
			handle_resize_matrix(&matrix_memory_size, &matrix_memory);
			break;
		default:
			return;
	}
}

void handle_load_matrix(int *size, MatrixRegistry **memory)
{
	(*size)++;
	*memory = realloc(*memory, (sizeof(MatrixRegistry)) * (*size));

	int rows_count, columns_count;

	scanf("%d %d", &rows_count, &columns_count);

	(*memory)[((*size) - 1)] = *read_matrix_registry(rows_count, columns_count);

	printf("Successfully saved the matrix to index %d\n", *size - 1); // TODO Delete
}

void handle_print_matrix_dimension(const int *size, MatrixRegistry **memory)
{
	int index;
	scanf("%d", &index);

	if (index >= *size) {
		printf("No matrix with the given index\n");
		return;
	}

	MatrixRegistry *registry = &(*memory)[index];

	printf("%d %d\n", registry->rows_count, registry->columns_count);
}

void handle_print_matrix(const int *size, MatrixRegistry **memory)
{
	int index;
	scanf("%d", &index);

	if (index >= *size) {
		printf("No matrix with the given index\n");
		return;
	}

	MatrixRegistry *registry = &(*memory)[index];

	print_matrix(registry);
}

void handle_resize_matrix(const int *size, MatrixRegistry **memory)
{
	int index, new_rows_count, new_columns_count;
	scanf("%d", &index);

	if (index >= *size) {
		printf("No matrix with the given index\n");
		return;
	}

	scanf("%d", &new_rows_count);
	int *new_rows = malloc(sizeof(int) * new_rows_count);

	for (int i = 0; i < new_rows_count; i++) {
		scanf("%d", &new_rows[i]);
	}

	scanf("%d", &new_columns_count);
	int *new_columns = malloc(sizeof(int) * new_columns_count);

	for (int i = 0; i < new_columns_count; i++) {
		scanf("%d", &new_columns[i]);
	}

	MatrixRegistry *registry = &(*memory)[index];

	MatrixRegistry *new_registry = create_from(registry, new_rows_count, new_rows,
											   new_columns_count, new_columns);

	(*memory)[index] = *new_registry;
}