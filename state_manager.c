//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <malloc.h>
#include "state_manager.h"

void handle_state(char state)
{
	static int matrix_memory_size = 0;
	static MatrixRegistry *matrix_memory;

	switch (state) {
		case 'L':
			handle_read(&matrix_memory_size, &matrix_memory);
			break;
		case 'D':
			handle_print_dimension(&matrix_memory_size, &matrix_memory);
			break;
		case 'P':
			handle_print(&matrix_memory_size, &matrix_memory);
			break;
		case 'C':
			handle_resize(&matrix_memory_size, &matrix_memory);
			break;
		case 'M':
			handle_multiply(&matrix_memory_size, &matrix_memory);
			break;
		case 'O':
			handle_sort(&matrix_memory_size, &matrix_memory);
			break;
		case 'T':
			handle_transpose(&matrix_memory_size, &matrix_memory);
			break;
		default:
			return;
	}
}

void handle_read(int *size, MatrixRegistry **memory)
{
	int rows_count, columns_count;

	scanf("%d %d", &rows_count, &columns_count);

	MatrixRegistry *registry = read_matrix_registry(rows_count, columns_count);

	handle_save(size, memory, registry);
}

void handle_save(int *size, MatrixRegistry **memory, MatrixRegistry *registry)
{
	(*size)++;
	*memory = realloc(*memory, (sizeof(MatrixRegistry)) * (*size));

	handle_save_at(*size - 1, memory, registry);
}

void handle_print_dimension(const int *size, MatrixRegistry **memory)
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

void handle_print(const int *size, MatrixRegistry **memory)
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

void handle_resize(const int *size, MatrixRegistry **memory)
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

	handle_save_at(index, memory, new_registry);
}

void handle_multiply(int *size, MatrixRegistry **memory)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);

	if (index1 >= *size || index2 >= *size) {
		printf("No matrix with the given index\n");
		return;
	}

	MatrixRegistry *registry1 = &(*memory)[index1];
	MatrixRegistry *registry2 = &(*memory)[index2];

	MatrixRegistry *new_registry = multiply(registry1, registry2);

	handle_save(size, memory, new_registry);
}

void handle_sort(const int *size, MatrixRegistry **memory)
{
	for (int i = 0; i < *size; i++) {
		for (int j = i + 1; j < *size; j++) {
			if (compare(&(*memory)[i], &(*memory)[j]) == 1) {
				MatrixRegistry *aux = malloc(sizeof(MatrixRegistry));
				*aux = (*memory)[i];
				(*memory)[i] = (*memory)[j];
				(*memory)[j] = *aux;
			}
		}
	}
}

void handle_transpose(const int *size, MatrixRegistry **memory)
{
	int index;
	scanf("%d", &index);

	if (index >= *size) {
		printf("No matrix with the given index\n");
		return;
	}

	MatrixRegistry *registry = &(*memory)[index];

	MatrixRegistry *new_registry = transpose(registry);

	handle_save_at(index, memory, new_registry);
}

void handle_save_at(int index, MatrixRegistry **memory, MatrixRegistry *registry)
{
	(*memory)[index] = *registry;

	printf("Successfully saved the matrix to index %d\n", index); // TODO Delete
}