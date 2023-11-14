//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <malloc.h>
#include "state_manager.h"

void handle_load_matrix(int *size, MatrixRegistry **memory);
void handle_print_matrix_dimension(int *size, MatrixRegistry **memory);
void handle_print_matrix(int *size, MatrixRegistry **memory);

void handle_state(char state)
{
	static int matrix_memory_size = 0;
	static MatrixRegistry *matrix_memory;

	switch (state) {
		case 'L':
			handle_load_matrix(&matrix_memory_size,&matrix_memory);
			break;
		case 'D':
			handle_print_matrix_dimension(&matrix_memory_size,&matrix_memory);
			break;
		case 'P':
			handle_print_matrix(&matrix_memory_size,&matrix_memory);
			break;
		default:
			return;
	}
}

void handle_load_matrix(int *size, MatrixRegistry **memory)
{
	(*size)++;
	*memory = realloc(memory, (sizeof(MatrixRegistry)) * (*size));

	*memory[((*size) - 1)] = *read_matrix_registry();

	printf("Successfully saved the matrix to index %d\n", *size - 1);

}

void handle_print_matrix_dimension(int *size, MatrixRegistry **memory)
{
	int index;
	scanf("%d", &index);

	MatrixRegistry *registry = memory[index];

	printf("%d %d\n", registry->rows_count, registry->columns_count);
}

void handle_print_matrix(int *size, MatrixRegistry **memory)
{
	int index;
	scanf("%d", &index);

	MatrixRegistry *registry = memory[index];

	print_matrix(registry);
}