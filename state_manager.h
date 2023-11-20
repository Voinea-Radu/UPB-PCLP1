//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include "registry_manager.h"

void handle_state(char command);

void handle_read(MatrixRegistry *registry);

void handle_save(MatrixRegistry *registry, Matrix *matrix);

void handle_save_at(MatrixRegistry *registry, unsigned int index, Matrix *matrix);

void handle_print_dimension(MatrixRegistry *registry);

void handle_print(MatrixRegistry *registry);

void handle_resize(MatrixRegistry *registry);

void handle_multiply(MatrixRegistry *registry);

void handle_sort(MatrixRegistry *registry);

void handle_transpose(MatrixRegistry *registry);

void handle_raise_to_power(MatrixRegistry *registry);

void handle_free(MatrixRegistry *registry);

void handle_multiply_strassen(MatrixRegistry *registry);

void handle_free_all(MatrixRegistry *registry);