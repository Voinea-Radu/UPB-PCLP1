//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include <stdio.h>
#include <malloc.h>
#include "registry_manager.h"

MatrixRegistry *read_matrix_registry()
{
	int n, m;

	scanf("%d %d", &n, &m);

	double **matrix = malloc(sizeof(double *) * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = malloc(sizeof(double) * m);
		for (int j = 0; j < m; j++) {
			scanf("%lf", &matrix[i][j]);
		}
	}

	MatrixRegistry *output_registry = malloc(sizeof(MatrixRegistry));

	output_registry->matrix = matrix;
	output_registry->rows_count = n;
	output_registry->columns_count = m;

	return output_registry;
}

void print_matrix(MatrixRegistry *registry)
{
	for (int i = 0; i < registry->rows_count; i++) {
		for (int j = 0; j < registry->columns_count; j++) {
			printf("%lf ", registry->matrix[i][j]);
		}
		printf("\n");
	}
}
