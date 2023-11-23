// ********************************************
// Copyright Voinea Radu-Mihai 315CAa 2023-2024
// ********************************************

#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include "registry_manager.h"

t_matrix *read_matrix_registry(unsigned int rows_count,
							   unsigned int columns_count)
{
	int **matrix = malloc(sizeof(int *) * rows_count);

	for (unsigned int i = 0; i < rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * columns_count);

		for (unsigned int j = 0; j < columns_count; j++)
			scanf("%d", &matrix[i][j]);
	}

	t_matrix *output_matrix = malloc(sizeof(t_matrix));

	output_matrix->data = matrix;
	output_matrix->rows_count = rows_count;
	output_matrix->columns_count = columns_count;

	return output_matrix;
}

void print_matrix(t_matrix *matrix)
{
	for (unsigned int i = 0; i < matrix->rows_count; i++) {
		for (unsigned int j = 0; j < matrix->columns_count; j++)
			printf("%d ", matrix->data[i][j]);

		printf("\n");
	}
}

t_matrix *create_from(t_matrix *matrix, unsigned int new_rows_count,
					  const unsigned int *new_rows,
					  unsigned int new_columns_count,
					  const unsigned int *new_columns)
{
	t_matrix *output_registry = malloc(sizeof(t_matrix));

	output_registry->rows_count = new_rows_count;
	output_registry->columns_count = new_columns_count;

	int **matrix_data = malloc(sizeof(int *) * new_rows_count);

	for (unsigned int i = 0; i < new_rows_count; i++) {
		matrix_data[i] = malloc(sizeof(int) * new_columns_count);

		for (unsigned int j = 0; j < new_columns_count; j++)
			matrix_data[i][j] = matrix->data[new_rows[i]][new_columns[j]];
	}

	output_registry->data = matrix_data;

	return output_registry;
}

t_matrix *multiply(t_matrix *matrix1, t_matrix *matrix2)
{
	if (matrix1->columns_count != matrix2->rows_count) {
		printf("Cannot perform matrix multiplication\n");
		return NULL;
	}

	t_matrix *output_matrix = malloc(sizeof(t_matrix));

	output_matrix->rows_count = matrix1->rows_count;
	output_matrix->columns_count = matrix2->columns_count;

	int **data = malloc(sizeof(int *) * output_matrix->rows_count);

	for (unsigned int i = 0; i < output_matrix->rows_count; i++) {
		data[i] = malloc(sizeof(int) * output_matrix->columns_count);

		for (unsigned int j = 0; j < output_matrix->columns_count; j++) {
			data[i][j] = 0;
			for (unsigned int k = 0; k < matrix1->columns_count; k++) {
				data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
				data[i][j] = mod(data[i][j]);
			}
		}
	}

	output_matrix->data = data;

	return output_matrix;
}

int compare(t_matrix *matrix1, t_matrix *matrix2)
{
	int sum1 = 0, sum2 = 0;

	for (unsigned int i = 0; i < matrix1->rows_count; i++) {
		for (unsigned int j = 0; j < matrix1->columns_count; j++) {
			sum1 += matrix1->data[i][j];
			sum1 = mod(sum1);
		}
	}

	for (unsigned int i = 0; i < matrix2->rows_count; i++) {
		for (unsigned int j = 0; j < matrix2->columns_count; j++) {
			sum2 += matrix2->data[i][j];
			sum2 = mod(sum2);
		}
	}

	return sum1 > sum2;
}

t_matrix *transpose(t_matrix *matrix)
{
	t_matrix *output_matrix = malloc(sizeof(t_matrix));

	output_matrix->rows_count = matrix->columns_count;
	output_matrix->columns_count = matrix->rows_count;

	int **matrix_data =
			malloc(sizeof(unsigned int *) * output_matrix->rows_count);

	for (unsigned int i = 0; i < output_matrix->rows_count; i++) {
		matrix_data[i] =
				malloc(sizeof(unsigned int) * output_matrix->columns_count);

		for (unsigned int j = 0; j < output_matrix->columns_count; j++)
			matrix_data[i][j] = matrix->data[j][i];
	}

	output_matrix->data = matrix_data;

	return output_matrix;
}

t_matrix *raise_to_power(t_matrix *matrix, int power)
{
	if (power < 0) {
		printf("Power should be positive\n");
		return NULL;
	}

	if (matrix->columns_count != matrix->rows_count) {
		printf("Cannot perform matrix multiplication\n");
		return NULL;
	}

	if (power == 0) {
		t_matrix *aux_matrix0 = malloc(sizeof(t_matrix));

		aux_matrix0->rows_count = matrix->rows_count;
		aux_matrix0->columns_count = matrix->columns_count;

		for (unsigned int i = 0; i < aux_matrix0->rows_count; i++)
			for (unsigned int j = 0; j < aux_matrix0->columns_count; j++)
				if (i == j)
					aux_matrix0->data[i][j] = 1;
				else
					aux_matrix0->data[i][j] = 0;

		return aux_matrix0;
	}

	if (power == 1) {
		t_matrix *aux_matrix1 = malloc(sizeof(t_matrix));

		aux_matrix1->rows_count = matrix->rows_count;
		aux_matrix1->columns_count = matrix->columns_count;

		int **matrix_data =
				malloc(sizeof(unsigned int *) * aux_matrix1->rows_count);

		for (unsigned int i = 0; i < aux_matrix1->rows_count; i++) {
			matrix_data[i] =
					malloc(sizeof(unsigned int) * aux_matrix1->columns_count);

			for (unsigned int j = 0; j < aux_matrix1->columns_count; j++)
				matrix_data[i][j] = matrix->data[i][j];
		}

		aux_matrix1->data = matrix_data;

		return aux_matrix1;
	}

	t_matrix *aux_matrix2 = raise_to_power(matrix, power / 2);
	t_matrix *aux_matrix3 = multiply(aux_matrix2, aux_matrix2);

	if (power % 2 == 0) {
		free_matrix(aux_matrix2);
		return aux_matrix3;
	}

	t_matrix *aux_matrix4 = multiply(aux_matrix3, matrix);

	free_matrix(aux_matrix2);
	free_matrix(aux_matrix3);

	return aux_matrix4;
}

void strassen_c(t_matrix *matrix1, t_matrix *matrix2,
				t_matrix **C1, t_matrix **C2, t_matrix **C3, t_matrix **C4)
{
	unsigned int *matrix_v1 =
			malloc(sizeof(int) * matrix1->rows_count / 2);

	unsigned int *matrix_v2 =
			malloc(sizeof(int) * matrix1->rows_count / 2);

	for (unsigned int i = 0; i < matrix1->rows_count / 2; i++) {
		matrix_v1[i] = i;
		matrix_v2[i] = i + matrix1->rows_count / 2;
	}

	t_matrix *A1 = create_from(matrix1, matrix1->rows_count / 2, matrix_v1,
							   matrix1->columns_count / 2, matrix_v1);
	t_matrix *A2 = create_from(matrix1, matrix1->rows_count / 2, matrix_v1,
							   matrix1->columns_count / 2, matrix_v2);
	t_matrix *A3 = create_from(matrix1, matrix1->rows_count / 2, matrix_v2,
							   matrix1->columns_count / 2, matrix_v1);
	t_matrix *A4 = create_from(matrix1, matrix1->rows_count / 2, matrix_v2,
							   matrix1->columns_count / 2, matrix_v2);

	t_matrix *B1 = create_from(matrix2, matrix2->rows_count / 2, matrix_v1,
							   matrix2->columns_count / 2, matrix_v1);
	t_matrix *B2 = create_from(matrix2, matrix2->rows_count / 2, matrix_v1,
							   matrix2->columns_count / 2, matrix_v2);
	t_matrix *B3 = create_from(matrix2, matrix2->rows_count / 2, matrix_v2,
							   matrix2->columns_count / 2, matrix_v1);
	t_matrix *B4 = create_from(matrix2, matrix2->rows_count / 2, matrix_v2,
							   matrix2->columns_count / 2, matrix_v2);

	free(matrix_v1);
	free(matrix_v2);

	t_matrix *sum1 = sum_matrix(A1, A4);
	t_matrix *sum2 = sum_matrix(B1, B4);
	t_matrix *sum3 = sum_matrix(A3, A4);
	t_matrix *sum4 = sum_matrix(A1, A2);
	t_matrix *sum5 = sum_matrix(B1, B2);
	t_matrix *sum6 = sum_matrix(B3, B4);

	t_matrix *sub1 = substract_matrix(B2, B4);
	t_matrix *sub2 = substract_matrix(B3, B1);
	t_matrix *sub3 = substract_matrix(A3, A1);
	t_matrix *sub4 = substract_matrix(A2, A4);

	t_matrix *M1 = multiply_strassen(sum1, sum2);
	t_matrix *M2 = multiply_strassen(sum3, B1);
	t_matrix *M3 = multiply_strassen(A1, sub1);
	t_matrix *M4 = multiply_strassen(A4, sub2);
	t_matrix *M5 = multiply_strassen(sum4, B4);
	t_matrix *M6 = multiply_strassen(sub3, sum5);
	t_matrix *M7 = multiply_strassen(sub4, sum6);

	free_multiple_matrix(4, A1, A2, A3, A4);
	free_multiple_matrix(4, B1, B2, B3, B4);
	free_multiple_matrix(6, sum1, sum2, sum3, sum4, sum5, sum6);
	free_multiple_matrix(4, sub1, sub2, sub3, sub4);

	t_matrix *sum7 = sum_matrix(M1, M4);
	t_matrix *sum8 = sum_matrix(M1, M3);

	t_matrix *sub5 = substract_matrix(sum7, M5);
	t_matrix *sub6 = substract_matrix(sum8, M2);

	*C1 = sum_matrix(sub5, M7);
	*C2 = sum_matrix(M3, M5);
	*C3 = sum_matrix(M2, M4);
	*C4 = sum_matrix(sub6, M6);

	free_multiple_matrix(2, sum7, sum8);
	free_multiple_matrix(2, sub5, sub6);
	free_multiple_matrix(7, M1, M2, M3, M4, M5, M6, M7);
}

t_matrix *multiply_strassen(t_matrix *matrix1, t_matrix *matrix2)
{
	if (matrix1->columns_count != matrix2->rows_count ||
		matrix1->columns_count != matrix1->rows_count ||
		matrix2->columns_count != matrix2->rows_count) {
		printf("Cannot perform matrix multiplication\n");
		return NULL;
	}

	if (matrix1->rows_count == 1) {
		t_matrix *output_registry = malloc(sizeof(t_matrix));

		output_registry->rows_count = 1;
		output_registry->columns_count = 1;
		int **matrix = malloc(sizeof(int *) * output_registry->rows_count);

		matrix[0] = malloc(sizeof(int) * output_registry->columns_count);

		matrix[0][0] = matrix1->data[0][0] * matrix2->data[0][0];
		output_registry->data = matrix;
		return output_registry;
	}

	t_matrix *C1, *C2, *C3, *C4;

	strassen_c(matrix1, matrix2, &C1, &C2, &C3, &C4);

	return exec_strassen(matrix1, matrix2, C1, C2, C3, C4);
}

t_matrix *exec_strassen(t_matrix *matrix1, t_matrix *matrix2,
						t_matrix *C1, t_matrix *C2, t_matrix *C3, t_matrix *C4)
{
	t_matrix *output_registry = malloc(sizeof(t_matrix));
	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix2->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);

	for (unsigned int i = 0; i < output_registry->rows_count; i++)
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);

	for (unsigned int i = 0; i < output_registry->rows_count / 2; i++)
		for (unsigned int j = 0; j < output_registry->columns_count / 2; j++) {
			unsigned int new_i = i + output_registry->rows_count / 2;
			matrix[i][j] = C1->data[i][j];
			matrix[i][j + output_registry->columns_count / 2] = C2->data[i][j];
			matrix[new_i][j] = C3->data[i][j];
			matrix[new_i][j + output_registry->columns_count / 2] =
					C4->data[i][j];
		}

	output_registry->data = matrix;

	free_matrix(C1);
	free_matrix(C2);
	free_matrix(C3);
	free_matrix(C4);

	return output_registry;
}

t_matrix *sum_matrix(t_matrix *matrix1, t_matrix *matrix2)
{
	t_matrix *output_registry = malloc(sizeof(t_matrix));

	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix1->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);
	for (unsigned int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);
		for (unsigned int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
			matrix[i][j] = mod(matrix[i][j]);
		}
	}

	output_registry->data = matrix;

	return output_registry;
}

t_matrix *substract_matrix(t_matrix *matrix1, t_matrix *matrix2)
{
	t_matrix *output_registry = malloc(sizeof(t_matrix));

	output_registry->rows_count = matrix1->rows_count;
	output_registry->columns_count = matrix1->columns_count;

	int **matrix = malloc(sizeof(int *) * output_registry->rows_count);
	for (unsigned int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(int) * output_registry->columns_count);
		for (unsigned int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
			matrix[i][j] = mod(matrix[i][j]);
		}
	}

	output_registry->data = matrix;

	return output_registry;
}

int mod(int number)
{
	number = number % MOD;
	if (number < 0)
		number += MOD;

	return number;
}

void free_matrix(t_matrix *matrix)
{
	for (unsigned int i = 0; i < matrix->rows_count; i++)
		free(matrix->data[i]);
	free(matrix->data);
	free(matrix);
}

void free_multiple_matrix(int number, ...)
{
	va_list arg_list;

	// Initializeaza arg_list pentru numarul de argumente
	va_start(arg_list, number);

	// Aceseaza toate argumentele
	for (int i = 0; i < number; i++)
		free_matrix(va_arg(arg_list, t_matrix *));

	// Elibereaza memoria pentru arg_list
	va_end(arg_list);
}

