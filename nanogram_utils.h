int check_nanogram(int number_of_lines, int number_of_columns,
				   const int **nanogram, const int **line_rules,
				   const int **column_rules);

int check_line(int number_of_columns, int line_index, const int **board,
			   const int *line_rules);

int check_column(int number_or_lines, int column_index, const int **board,
				 const int *column_rules);
