//
// Nume: Voinea Radu-Mihai
// Grupa: 315 CA
//

#include "registry_manager.h"

void handle_state(char state);

void handle_read(int *size, MatrixRegistry **memory);

void handle_save(int *size, MatrixRegistry **memory, MatrixRegistry *registry);

void handle_save_at(int index, MatrixRegistry **memory, MatrixRegistry *registry);

void handle_print_dimension(const int *size, MatrixRegistry **memory);

void handle_print(const int *size, MatrixRegistry **memory);

void handle_resize(const int *size, MatrixRegistry **memory);

void handle_multiply(int *size, MatrixRegistry **memory);

void handle_sort(const int *size, MatrixRegistry **memory);

void handle_transpose(const int *size, MatrixRegistry **memory);