//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <stdio.h>
#include <malloc.h>
#include "registry_manager.h"

Matrix *read_matrix_registry(int rows_count, int columns_count)
{
	double **matrix = malloc(sizeof(double *) * rows_count);
	for (int i = 0; i < rows_count; i++) {
		matrix[i] = malloc(sizeof(double) * columns_count);
		for (int j = 0; j < columns_count; j++) {
			scanf("%lf", &matrix[i][j]);
		}
	}

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->matrix = matrix;
	output_registry->rows_count = rows_count;
	output_registry->columns_count = columns_count;

	return output_registry;
}

void print_matrix(Matrix *registry)
{
	for (int i = 0; i < registry->rows_count; i++) {
		for (int j = 0; j < registry->columns_count; j++) {
			printf("%lf ", registry->matrix[i][j]);
		}
		printf("\n");
	}
}

Matrix *create_from(Matrix *registry, int new_rows_count, const int *new_rows,
					int new_columns_count, const int *new_columns)
{

	printf("Creating new matrix from rows(%d): ", new_rows_count);
	for (int i = 0; i < new_rows_count; i++) {
		printf("%d ", new_rows[i]);
	}
	printf("\n");
	printf("Creating new matrix from columns(%d): ", new_columns_count);
	for (int i = 0; i < new_columns_count; i++) {
		printf("%d ", new_columns[i]);
	}
	printf("\n");

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = new_rows_count;
	output_registry->columns_count = new_columns_count;

	double **matrix = malloc(sizeof(double *) * new_rows_count);
	for (int i = 0; i < new_rows_count; i++) {
		matrix[i] = malloc(sizeof(double) * new_columns_count);
		for (int j = 0; j < new_columns_count; j++) {
			matrix[i][j] = registry->matrix[new_rows[i]][new_columns[j]];
			printf("%f ", registry->matrix[new_rows[i]][new_columns[j]]);
		}
		printf("\n");
	}

	output_registry->matrix = matrix;

	return output_registry;
}

Matrix *multiply(Matrix *registry1, Matrix *registry2)
{
	if (registry1->columns_count != registry2->rows_count) {
		printf("Cannot perform matrix multiplication");
		return NULL;
	}

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = registry1->rows_count;
	output_registry->columns_count = registry2->columns_count;

	double **matrix = malloc(sizeof(double *) * output_registry->rows_count);
	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(double) * output_registry->columns_count);
		for (int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = 0;
			for (int k = 0; k < registry1->columns_count; k++) {
				matrix[i][j] += registry1->matrix[i][k] * registry2->matrix[k][j];
			}
		}
	}

	output_registry->matrix = matrix;

	return output_registry;
}

int compare(Matrix *registry1, Matrix *registry2)
{
	// compare the sum of elements
	double sum1 = 0, sum2 = 0;
	for (int i = 0; i < registry1->rows_count; i++) {
		for (int j = 0; j < registry1->columns_count; j++) {
			sum1 += registry1->matrix[i][j];
		}
	}

	for (int i = 0; i < registry2->rows_count; i++) {
		for (int j = 0; j < registry2->columns_count; j++) {
			sum2 += registry2->matrix[i][j];
		}
	}

	if (sum1 == sum2) {
		return 0;
	}

	return sum1 > sum2 ? 1 : -1;
}

Matrix *transpose(Matrix *registry)
{
	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = registry->columns_count;
	output_registry->columns_count = registry->rows_count;

	double **matrix = malloc(sizeof(double *) * output_registry->rows_count);
	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(double) * output_registry->columns_count);
		for (int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = registry->matrix[j][i];
		}
	}

	output_registry->matrix = matrix;

	return output_registry;
}

Matrix *raise_to_power(Matrix *registry, int power)
{
	if (power < 0) {
		printf("Power should be positive");
		return NULL;
	}

	if (registry->columns_count != registry->rows_count) {
		printf("Cannot perform matrix multiplication");
		return NULL;
	}

	Matrix *output_registry = malloc(sizeof(Matrix));

	output_registry->rows_count = registry->rows_count;
	output_registry->columns_count = registry->columns_count;

	double **matrix = malloc(sizeof(double *) * output_registry->rows_count);
	for (int i = 0; i < output_registry->rows_count; i++) {
		matrix[i] = malloc(sizeof(double) * output_registry->columns_count);
		for (int j = 0; j < output_registry->columns_count; j++) {
			matrix[i][j] = registry->matrix[i][j];
		}
	}

	output_registry->matrix = matrix;

	if (power == 0) {
		for (int i = 0; i < output_registry->rows_count; i++) {
			for (int j = 0; j < output_registry->columns_count; j++) {
				if (i == j) {
					output_registry->matrix[i][j] = 1;
				} else {
					output_registry->matrix[i][j] = 0;
				}
			}
		}
		return output_registry;
	}

	if (power == 1) {
		return output_registry;
	}

	Matrix *aux_registry = raise_to_power(registry, power / 2);
	Matrix *aux_registry2 = multiply(aux_registry, aux_registry);

	if (power % 2 == 0) {
		return aux_registry2;
	}

	Matrix *aux_registry3 = multiply(aux_registry2, registry);

	return aux_registry3;
}
