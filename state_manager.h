// ********************************************
// Copyright Voinea Radu-Mihai 315CAa 2023-2024
// ********************************************

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "registry_manager.h"

/**
 * In functie de comanda primita apeleaza functia asocitata sau afiseaza o
 * eroare in cazul in care comanda nu este asociata unei functii
 * @param command Comanda primita de la tastatura
 */
void handle_state(char command);

/**
 * Citeste o matrice de la tastatura si o adauga in registry
 * @param registry Registry-ul in care se adauga matricea
 */
void handle_read(t_matrix_registry *registry);

/**
 * Citeste o matrice de la tastatura si o adauga in registry la indexul dat
 * @param registry Registry-ul in care se adauga matricea
 * @param matrix   Matricea care se adauga
 */
void handle_save(t_matrix_registry *registry, t_matrix *matrix);

/**
 * Salveaza o matrice in registry la indexul dat
 * @param registry Registry-ul in care se adauga matricea
 * @param index    Indexul la care se salveaza matricea
 * @param matrix   Matricea care se adauga
 */
void handle_save_at(t_matrix_registry *registry, unsigned int index,
					t_matrix *matrix);

/**
 * Afiseaza dimensiunea unei matrice din registry
 * @param registry Registry-ul din care se afiseaza dimensiunea
 */
void handle_print_dimension(t_matrix_registry *registry);

/**
 * Afiseaza o matrice din registry
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_print(t_matrix_registry *registry);

/**
 * Modifica o matricea in registry la index-ul citit
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_resize(t_matrix_registry *registry);

/**
 * Inmulteste 2 matrici din registry la index-urile citite
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_multiply(t_matrix_registry *registry);

/**
 * Sorteaza registry-ul de matrici
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_sort(t_matrix_registry *registry);

/**
 * Calculeaza transpuna unei matrici din registry la index-ul citit
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_transpose(t_matrix_registry *registry);

/**
 * Ridica o matrice din registry la puterea citita
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_raise_to_power(t_matrix_registry *registry);

/**
 * Sterge o matrice din registry la indexul dat
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_free(t_matrix_registry *registry);

/**
 * Inmulteste 2 matrici din registry la index-urile citite folosind algoritmul
 * Strassen
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_multiply_strassen(t_matrix_registry *registry);

/**
 * Elimina toate matricile din registry
 * @param registry Registry-ul din care se afiseaza matricea
 */
void handle_free_all(t_matrix_registry *registry);

#endif // STATE_MANAGER_H
