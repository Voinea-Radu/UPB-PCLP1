// ********************************************
// Copyright Voinea Radu-Mihai 315CAa 2023-2024
// ********************************************

#include <malloc.h>
#include "state_manager.h"

void handle_state(char command)
{
	static t_matrix_registry *registry;

	if (!registry) {
		registry = malloc(sizeof(t_matrix_registry));
		registry->size = 0;
		registry->capacity = 1;
		registry->matrices = malloc(sizeof(t_matrix));
	}

	switch (command) {
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
	case 'F':
		handle_free(registry);
		break;
	case 'S':
		handle_multiply_strassen(registry);
		break;
	case 'Q':
		handle_free_all(registry);
		break;
	default:
		printf("Unrecognized command\n");
		//printf("Unrecognized command '%c'\n", command);
		return;
	}
}

void handle_read(t_matrix_registry *registry)
{
	int rows_count, columns_count;

	scanf("%d %d", &rows_count, &columns_count);

	t_matrix *matrix = read_matrix_registry(rows_count, columns_count);

	handle_save(registry, matrix);
}

void handle_save(t_matrix_registry *registry, t_matrix *matrix)
{
	registry->size++;

	if (registry->size > registry->capacity) {
		registry->capacity *= 2;
		registry->matrices =
				realloc(registry->matrices,
						(sizeof(t_matrix)) * registry->capacity);
	}

	handle_save_at(registry, registry->size - 1, matrix);
}

void handle_print_dimension(t_matrix_registry *registry)
{
	unsigned int index;
	scanf("%u", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix = &registry->matrices[index];

	printf("%d %d\n", matrix->rows_count, matrix->columns_count);
}

void handle_print(t_matrix_registry *registry)
{
	unsigned int index;
	scanf("%u", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix = &registry->matrices[index];

	print_matrix(matrix);
}

void handle_resize(t_matrix_registry *registry)
{
	unsigned int index, new_rows_count, new_columns_count;
	scanf("%u", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	scanf("%u", &new_rows_count);
	unsigned int *new_rows = malloc(sizeof(int) * new_rows_count);

	for (unsigned int i = 0; i < new_rows_count; i++)
		scanf("%u", &new_rows[i]);

	scanf("%u", &new_columns_count);
	unsigned int *new_columns = malloc(sizeof(int) * new_columns_count);

	for (unsigned int i = 0; i < new_columns_count; i++)
		scanf("%u", &new_columns[i]);

	t_matrix *matrix = &registry->matrices[index];

	t_matrix *new_matrix = create_from(matrix, new_rows_count, new_rows,
									   new_columns_count, new_columns);

	handle_save_at(registry, index, new_matrix);
}

void handle_multiply(t_matrix_registry *registry)
{
	unsigned int index1, index2;
	scanf("%u %u", &index1, &index2);

	if (index1 >= registry->size || index2 >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix1 = &registry->matrices[index1];
	t_matrix *matrix2 = &registry->matrices[index2];

	t_matrix *matrix = multiply(matrix1, matrix2);

	if (!matrix)
		return;

	handle_save(registry, matrix);
}

void handle_sort(t_matrix_registry *registry)
{
	for (unsigned int i = 0; i < registry->size; i++) {
		for (unsigned int j = i + 1; j < registry->size; j++) {
			if (compare(&registry->matrices[i],
						&registry->matrices[j])) {
				t_matrix temp = registry->matrices[i];
				registry->matrices[i] = registry->matrices[j];
				registry->matrices[j] = temp;
			}
		}
	}
}

void handle_transpose(t_matrix_registry *registry)
{
	unsigned int index;
	scanf("%u", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix = &registry->matrices[index];
	t_matrix *new_matrix = transpose(matrix);

	handle_save_at(registry, index, new_matrix);
}

void handle_save_at(t_matrix_registry *registry,
					unsigned int index, t_matrix *matrix)
{
	registry->matrices[index] = *matrix;
}

void handle_raise_to_power(t_matrix_registry *registry)
{
	unsigned int index;
	int power;
	scanf("%u%d", &index, &power);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix = &registry->matrices[index];

	t_matrix *new_matrix = raise_to_power(matrix, power);

	if (!new_matrix)
		return;

	handle_save_at(registry, index, new_matrix);
}

void handle_free(t_matrix_registry *registry)
{
	unsigned int index;

	scanf("%ud", &index);

	if (index >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix = &registry->matrices[index];

	for (unsigned int i = 0; i < matrix->rows_count; i++)
		free(matrix->data[i]);

	free(matrix->data);

	for (unsigned int i = index; i < registry->size - 1; i++)
		registry->matrices[i] = registry->matrices[i + 1];

	registry->size--;
}

void handle_multiply_strassen(t_matrix_registry *registry)
{
	unsigned int index1, index2;
	scanf("%u %u", &index1, &index2);

	if (index1 >= registry->size || index2 >= registry->size) {
		printf("No matrix with the given index\n");
		return;
	}

	t_matrix *matrix1 = &registry->matrices[index1];
	t_matrix *matrix2 = &registry->matrices[index2];

	t_matrix *matrix = multiply_strassen(matrix1, matrix2);

	if (!matrix)
		return;

	handle_save(registry, matrix);
}

void handle_free_all(t_matrix_registry *registry)
{
	for (unsigned int i = 0; i < registry->size; i++) {
		t_matrix *matrix = &registry->matrices[i];

		for (unsigned int j = 0; j < matrix->rows_count; j++)
			free(matrix->data[j]);

		free(matrix->data);
	}

	free(registry->matrices);
	free(registry);
}
