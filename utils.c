#include <malloc.h>
#include "utils.h"

int *read_int_array(int size)
{
	int *array = (int *)malloc(size * sizeof(int));

	for (int index = 0; index < size; index++)
		scanf("%d", &array[index]);

	return array;
}

int **read_int_matrix(int rows, int columns)
{
	int **matrix = (int **)malloc(rows * sizeof(int *));

	for (int row_index = 0; row_index < rows; row_index++) {
		matrix[row_index] = (int *)malloc(columns * sizeof(int));

		for (int column_index = 0; column_index < columns; column_index++)
			scanf("%d", &matrix[row_index][column_index]);
	}

	return matrix;
}

