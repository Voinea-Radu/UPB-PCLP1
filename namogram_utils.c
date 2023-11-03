#include <stdio.h>
#include "namogram_utils.h"

int check_nanogram(int number_of_lines, int number_of_columns,
				   const int **nanogram, const int **line_rules,
				   const int **column_rules)
{
	for (int line_index = 0; line_index < number_of_lines; line_index++) {
		if (!check_line(number_of_columns, line_index, nanogram,
						line_rules[line_index])) {
			printf("Failed line %d\n", line_index);
			return 0;
		}
	}

	for (int column_index = 0; column_index < number_of_columns;
		 column_index++) {
		if (!check_column(number_of_lines, column_index,
						  nanogram,
						  (const int *)column_rules[column_index]
		)) {
			printf("Failed column %d\n", column_index);
			return 0;
		}
	}

	return 1;
}

int check_line(int number_of_columns, int line_index, const int **board,
			   const int *line_rules)
{
	int number_of_rules = line_rules[0];
	int index = 0;

	for (int rule_index = 1; rule_index <= number_of_rules; rule_index++) {
		int rule = line_rules[rule_index];
		int current_length = 0;

		while (board[line_index][index] == 0) {
			index++;

			if (index >= number_of_columns)
				return 0;
		}

		while (board[line_index][index] == 1) {
			index++;
			current_length++;

			if (index >= number_of_columns)
				break;
		}

		if (current_length == rule)
			continue;

		return 0;
	}

	return 1;
}

int check_column(int number_or_lines, int column_index, const int **board,
				 const int *column_rules)
{
	int number_of_rules = column_rules[0];
	int index = 0;

	for (int rule_index = 1; rule_index <= number_of_rules; rule_index++) {
		int rule = column_rules[rule_index];
		int current_length = 0;

		while (board[index][column_index] == 0) {
			index++;

			if (index >= number_or_lines)
				return 0;
		}

		while (board[index][column_index] == 1) {
			index++;
			current_length++;

			if (index >= number_or_lines)
				break;
		}

		if (current_length == rule)
			continue;

		return 0;
	}

	return 1;
}
