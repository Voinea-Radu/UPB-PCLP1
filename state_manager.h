//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include "registry_manager.h"

void handle_state(char command);

void handle_read(t_matrix_registry *registry);

void handle_save(t_matrix_registry *registry, t_matrix *matrix);

void handle_save_at(t_matrix_registry *registry, unsigned int index,
					t_matrix *matrix);

void handle_print_dimension(t_matrix_registry *registry);

void handle_print(t_matrix_registry *registry);

void handle_resize(t_matrix_registry *registry);

void handle_multiply(t_matrix_registry *registry);

void handle_sort(t_matrix_registry *registry);

void handle_transpose(t_matrix_registry *registry);

void handle_raise_to_power(t_matrix_registry *registry);

void handle_free(t_matrix_registry *registry);

void handle_multiply_strassen(t_matrix_registry *registry);

void handle_free_all(t_matrix_registry *registry);
