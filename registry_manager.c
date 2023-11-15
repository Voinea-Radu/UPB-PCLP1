//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <stdio.h>
#include <malloc.h>
#include "registry_manager.h"

Matrix *read_matrix_registry(int rows_count, int columns_count)
{
	int **matrix = malloc(sizeof(int *) * rows_count);
	for (int i = 0; i < rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * columns_count);
		for (int j = 0; j < columns_count; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->data = matrix;
	output_registry->rows_count = rows_count;
	output_registry->columns_count = columns_count;

	return output_registry;
}

void print_matrix(Matrix *matrix)
{
	for (int i = 0; i < matrix->rows_count; i++) {
		for (int j = 0; j < matrix->columns_count; j++) {
			printf("%d ", matrix->data[i][j]);
		}
		printf("\n");
	}
}

Matrix *create_from(Matrix *matrix, unsigned int new_rows_count, const unsigned int *new_rows,
					unsigned int new_columns_count, const unsigned int *new_columns)
{

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = new_rows_count;
	output_registry->columns_count = new_columns_count;

	int **matrix_data = malloc(sizeof(int *) * new_rows_count);
	for (int i = 0; i < new_rows_count; i++) {
		matrix_data[i] = malloc(sizeof(int) * new_columns_count);
		for (int j = 0; j < new_columns_count; j++) {
			matrix_data[i][j] = matrix->data[new_rows[i]][new_columns[j]];
		}
	}

	output_registry->data = matrix_data;

	return output_registry;
}

Matrix *multiply(Matrix *matrix1, Matrix *matrix2)
{
	if (matrix1->columns_count != matrix2->rows_count) {
		printf("Cannot perform data multiplication\n");
		return NULL;
	}

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix2->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);
	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);
		for (int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = 0;
			for (int k = 0; k < matrix1->columns_count; k++) {
				matrix[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
				matrix[i][j] %= MOD;
			}
		}
	}

	output_registry->data = matrix;

	return output_registry;
}

int compare(Matrix *matrix1, Matrix *matrix2)
{
	int sum1 = 0, sum2 = 0;

	for (int i = 0; i < matrix1->rows_count; i++) {
		for (int j = 0; j < matrix1->columns_count; j++) {
			sum1 += matrix1->data[i][j];
			sum1 %= MOD;
		}
	}

	for (int i = 0; i < matrix2->rows_count; i++) {
		for (int j = 0; j < matrix2->columns_count; j++) {
			sum2 += matrix2->data[i][j];
			sum2 %= MOD;
		}
	}

	return sum1 > sum2;
}

Matrix *transpose(Matrix *matrix)
{
	Matrix *output_matrix = malloc(sizeof(Matrix));

	output_matrix->rows_count = matrix->columns_count;
	output_matrix->columns_count = matrix->rows_count;

	int **matrix_data = malloc(sizeof(int *) * output_matrix->rows_count);
	for (int i = 0; i < output_matrix->rows_count; i++) {
		matrix_data[i] = malloc(sizeof(int) * output_matrix->columns_count);
		for (int j = 0; j < output_matrix->columns_count; j++) {
			matrix_data[i][j] = matrix->data[j][i];
		}
	}

	output_matrix->data = matrix_data;

	return output_matrix;
}

Matrix *raise_to_power(Matrix *matrix, int power)
{
	if (power < 0) {
		printf("Power should be positive\n");
		return NULL;
	}

	if (matrix->columns_count != matrix->rows_count) {
		printf("Cannot perform matrix_data multiplication\n");
		return NULL;
	}

	Matrix *output_matrix = malloc(sizeof(Matrix));

	output_matrix->rows_count = matrix->rows_count;
	output_matrix->columns_count = matrix->columns_count;

	int **matrix_data = malloc(sizeof(int *) * output_matrix->rows_count);
	for (int i = 0; i < output_matrix->rows_count; i++) {
		matrix_data[i] = malloc(sizeof(int) * output_matrix->columns_count);
		for (int j = 0; j < output_matrix->columns_count; j++) {
			matrix_data[i][j] = matrix->data[i][j];
		}
	}

	output_matrix->data = matrix_data;

	if (power == 0) {
		for (int i = 0; i < output_matrix->rows_count; i++) {
			for (int j = 0; j < output_matrix->columns_count; j++) {
				if (i == j) {
					output_matrix->data[i][j] = 1;
				} else {
					output_matrix->data[i][j] = 0;
				}
			}
		}
		return output_matrix;
	}

	if (power == 1) {
		return output_matrix;
	}

	Matrix *aux_registry = raise_to_power(matrix, power / 2);
	Matrix *aux_registry2 = multiply(aux_registry, aux_registry);

	if (power % 2 == 0) {
		return aux_registry2;
	}

	Matrix *aux_registry3 = multiply(aux_registry2, matrix);

	return aux_registry3;
}

//Implement the Strassen algorithm for data multiplication
Matrix *multiply_strassen(Matrix *matrix1, Matrix *matrix2)
{
	if (matrix1->columns_count != matrix2->rows_count || matrix1->columns_count != matrix1->rows_count ||
		matrix2->columns_count != matrix2->rows_count) {
		printf("Cannot perform data multiplication\n");
		return NULL;
	}

	if (matrix1->rows_count == 1) {
		Matrix *output_registry = malloc(sizeof(Matrix));
		output_registry->rows_count = 1;
		output_registry->columns_count = 1;
		int **matrix = malloc(sizeof(int *) * output_registry->rows_count);
		matrix[0] = malloc(sizeof(int) * output_registry->columns_count);
		matrix[0][0] = matrix1->data[0][0] * matrix2->data[0][0];
		output_registry->data = matrix;
		return output_registry;
	}

	unsigned int *matrix_v1 = malloc(sizeof(int) * matrix1->rows_count / 2);
	unsigned int *matrix_v2 = malloc(sizeof(int) * matrix1->rows_count / 2);

	for (unsigned int i = 0; i < matrix1->rows_count / 2; i++) {
		matrix_v1[i] = i;
		matrix_v2[i] = i + matrix1->rows_count / 2;
	}

	Matrix *A1 = create_from(matrix1, matrix1->rows_count / 2, matrix_v1,
							 matrix1->columns_count / 2, matrix_v1);
	Matrix *A2 = create_from(matrix1, matrix1->rows_count / 2, matrix_v1,
							 matrix1->columns_count / 2, matrix_v2);
	Matrix *A3 = create_from(matrix1, matrix1->rows_count / 2, matrix_v2,
							 matrix1->columns_count / 2, matrix_v1);
	Matrix *A4 = create_from(matrix1, matrix1->rows_count / 2, matrix_v2,
							 matrix1->columns_count / 2, matrix_v2);

	Matrix *B1 = create_from(matrix2, matrix2->rows_count / 2, matrix_v1,
							 matrix2->columns_count / 2, matrix_v1);
	Matrix *B2 = create_from(matrix2, matrix2->rows_count / 2, matrix_v1,
							 matrix2->columns_count / 2, matrix_v2);
	Matrix *B3 = create_from(matrix2, matrix2->rows_count / 2, matrix_v2,
							 matrix2->columns_count / 2, matrix_v1);
	Matrix *B4 = create_from(matrix2, matrix2->rows_count / 2, matrix_v2,
							 matrix2->columns_count / 2, matrix_v2);

	Matrix *M1 = multiply_strassen(sum_matrix(A1, A4), sum_matrix(B1, B4));
	Matrix *M2 = multiply_strassen(sum_matrix(A3, A4), B1);
	Matrix *M3 = multiply_strassen(A1, substract_matrix(B2, B4));
	Matrix *M4 = multiply_strassen(A4, substract_matrix(B3, B1));
	Matrix *M5 = multiply_strassen(sum_matrix(A1, A2), B4);
	Matrix *M6 = multiply_strassen(substract_matrix(A3, A1), sum_matrix(B1, B2));
	Matrix *M7 = multiply_strassen(substract_matrix(A2, A4), sum_matrix(B3, B4));

	Matrix *C1 = sum_matrix(substract_matrix(sum_matrix(M1, M4), M5), M7);
	Matrix *C2 = sum_matrix(M3, M5);
	Matrix *C3 = sum_matrix(M2, M4);
	Matrix *C4 = sum_matrix(substract_matrix(sum_matrix(M1, M3), M2), M6);

	Matrix *output_registry = malloc(sizeof(Matrix));
	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix2->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);

	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);
	}

	for (int i = 0; i < output_registry->rows_count / 2; i++) {
		for (int j = 0; j < output_registry->columns_count / 2; j++) {
			matrix[i][j] = C1->data[i][j];
			matrix[i][j + output_registry->columns_count / 2] = C2->data[i][j];
			matrix[i + output_registry->rows_count / 2][j] = C3->data[i][j];
			matrix[i + output_registry->rows_count / 2][j + output_registry->columns_count / 2] = C4->data[i][j];
		}
	}

	output_registry->data = matrix;

	return output_registry;
}

Matrix *sum_matrix(Matrix *matrix1, Matrix *matrix2)
{
	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix1->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);
	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);
		for (int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
		}
	}

	output_registry->data = matrix;

	return output_registry;
}

Matrix *substract_matrix(Matrix *matrix1, Matrix *matrix2)
{
	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix1->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);
	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);
		for (int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
		}
	}

	output_registry->data = matrix;

	return output_registry;
}