#include <stdio.h>
#include <malloc.h>
#include "utils.h"
#include "nanogram_utils.h"

void read_and_check_nanogram(void);

int main(void)
{
	int number_of_puzzles;

	// Citim numarul de nanograme
	scanf("%d", &number_of_puzzles);

	for (int puzzle_index = 0; puzzle_index < number_of_puzzles;
		 puzzle_index++) {
		read_and_check_nanogram();
	}

	return 0;
}

void read_and_check_nanogram(void)
{
	int number_of_lines, number_of_columns;

	// Citim dimensiunile nanogramei
	scanf("%d%d", &number_of_lines, &number_of_columns);

	int **line_rules = (int **)malloc(number_of_lines * sizeof(int *));
	int **column_rules = (int **)malloc
			(number_of_columns * sizeof(int *));

	for (int line_index = 0; line_index < number_of_lines; line_index++) {
		int number_of_rules;
		scanf("%d", &number_of_rules);

		// Alocam memorie pentru numarul de reguli de pe linia curenta si
		// pentru a stoca numarul acestora
		line_rules[line_index] = (int *)malloc
				((number_of_rules + 1) * sizeof(int));
		line_rules[line_index][0] = number_of_rules;

		// Citim regulile
		for (int rule_index = 1; rule_index <= number_of_rules; rule_index++)
			scanf("%d", &line_rules[line_index][rule_index]);
	}

	for (int column_index = 0; column_index < number_of_columns;
		 column_index++) {
		int number_of_rules;
		scanf("%d", &number_of_rules);

		// Alocam memorie pentru numarul de reguli de pe coloana curenta si
		// pentru a stoca numarul acestora
		column_rules[column_index] = (int *)malloc
				((number_of_rules + 1) * sizeof(int));
		column_rules[column_index][0] = number_of_rules;

		// Citim regulile
		for (int rule_index = 1; rule_index <= number_of_rules; rule_index++)
			scanf("%d", &column_rules[column_index][rule_index]);
	}

	// Citim nanograma
	int **nanogram = read_int_matrix(number_of_lines,
									 number_of_columns);

	int result = check_nanogram(number_of_lines, number_of_columns,
								(const int **)nanogram,
								(const int **)line_rules,
								(const int **)column_rules);
	printf("%s", result == 1 ? "Corect" : "Eroare");
}
