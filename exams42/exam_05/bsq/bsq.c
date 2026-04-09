/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:54:57 by yukravch          #+#    #+#             */
/*   Updated: 2025/12/09 13:10:52 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char**	ft_bsq(char* stream) {


	t_matrix	m;
	init_m(&m);
	
	if (fill_struct(&m, stream) == 1) {

		if (m.dp) { free_dp(m); }
		if (m.header) { free(m.header); }
		if (m.matrix) {  free_matrix(m.matrix);  }
		return NULL;
	}
	if (error_in_parsing(m)) {  
		
		if (m.dp) { free_dp(m); }
		if (m.header) { free(m.header); }
		if (m.matrix) {  free_matrix(m.matrix);  }
		return NULL;
	}
	
	dp(&m);
	get_coordinate_of_square(&m);
	change_matrix(&m);
	
	if (m.dp) {  free_dp(m);  }
	if (m.header) {  free(m.header);  }

	return m.matrix;
}

void	init_m(t_matrix* m) {

	m->header = NULL;
	m->matrix = NULL;
	m->dp = NULL;
	m->line_nb = 0;
	m->col_nb = 0;
}

int	fill_struct(t_matrix* m, char* stream) {

	if (get_matrix(stream, m) == 1)
		return 1;
	
	if (!m->header)
		return 1;
	int header_len = strlen(m->header);

	m->empty = m->header[header_len - 3];
	m->obstacle = m->header[header_len - 2];
	m->full = m->header[header_len - 1];

	if (!m->matrix)
		return 1;
	int	i = 0;
	while (m->matrix[0][i]) {  i++;  }
	m->col_nb = i;

	return 0;
}

int	get_matrix(char* file, t_matrix* m) {

	if (file) {
		FILE* stream = fopen(file, "r");
		if (!stream)
			return 1;
		if (ft_getline(stream, m) == 1) {  fclose(stream); return 1;  }
		fclose(stream);
	}
	else
		if (ft_getline(stdin, m) == 1)
			return 1;
	return 0;
}

int	ft_getline(FILE* stream, t_matrix* m) {

	
	size_t	i = 0;
	int	line_nb = 0;

	char*	buffer = NULL;
	size_t	buffer_size = 0;
	
	int	return_value = 0;
	
	return_value = getline(&buffer, &buffer_size, stream);
	if (return_value == -1) {  free(buffer); return 1;  }
	m->header = ft_strdup(buffer);
	if (!m->header) {  free(buffer); return 1;  }
	
	while (return_value != -1) {

		return_value = getline(&buffer, &buffer_size, stream);
		if (return_value == -1)
			break ;

		m->line_nb++;
		m->matrix = realloc(m->matrix, sizeof(char*) * (m->line_nb + 1));
		if (m->matrix == NULL) {  free(buffer); return 1;  }
		
		m->matrix[i] = ft_strdup(buffer);
		if (!m->matrix[i]) {  free(buffer); return 1;  }
		i++;
		m->matrix[i] = NULL;
	}
	free(buffer);
	return 0;
}


bool	error_in_parsing(t_matrix m) {

	int	header_len = strlen(m.header);
	if (!m.matrix || !m.header)
		return true;
	if (!isdigit(m.header[0]) || header_len < 4)
		return true;


	int i = 0;
	while (isdigit(m.header[i])) {  i++;  }
	char*	number_half = calloc(i + 1, sizeof(char));
	if (!number_half)
		return true;
	char*	elem_half = calloc(header_len - i + 1, sizeof(char));
	if (!elem_half) {
		free(number_half);
		return true;
	}
	
	for (int j = 0; j < i; j++) {  number_half[j] = m.header[j];  }
	for (int j = 0; m.header[i]; j++) {  elem_half[j] = m.header[i]; i++;  }

	int	nb_in_header = atoi(number_half);
	if (nb_in_header <= 0 || nb_in_header != m.line_nb || strlen(elem_half) != 3) {  free(number_half); free(elem_half); return true;  }
	if (elem_half[0] == elem_half[1] || elem_half[0] == elem_half[2] || elem_half[1] == elem_half[2]) { free(number_half); free(elem_half); return true;  }

	for (int i = 1; m.matrix[i]; i++) {
		if (strlen(m.matrix[i]) != m.col_nb) {  free(number_half); free(elem_half); return true;  }
	}

	for (int i = 0; m.matrix[i]; i++){
		for (int j = 0; m.matrix[i][j]; j++) {
			if (m.matrix[i][j] != m.empty && m.matrix[i][j] != m.obstacle) {  free(number_half); free(elem_half); return true;  }
		}
	}

	free(number_half);
	free(elem_half);
	return false;
}

void	dp( t_matrix* m ) {

	int	i = 0;
	int	j;
	m->dp = calloc(m->line_nb, sizeof(int*));

	for (int i = 0; i < m->line_nb; i++) {  m->dp[i] = calloc(m->col_nb, sizeof(int));  }

	while (i < m->line_nb && m->matrix[i]) {

		j = 0;
		while (j < m->col_nb && m->matrix[i][j]) {

			if (m->matrix[i][j] == m->obstacle) {
				m->dp[i][j] = 0;
			}
			else if (i == 0 || j == 0) {
				m->dp[i][j] = 1;
			}
			else {
				m->dp[i][j] = ft_min(m->dp[i-1][j], m->dp[i][j-1], m->dp[i-1][j-1]) + 1;
			}
			j++;
		}
		i++;
	}

}

void	get_coordinate_of_square(t_matrix* m) {

	int	biggest_i = 0;
	int	biggest_j = 0;
	int	biggest_dp = 0;

	for (int i = 0; i < m->line_nb; i++) {
		for (int j = 0; j < m->col_nb; j++) {

			if (m->dp[i][j] > biggest_dp) {
				biggest_dp = m->dp[i][j];
				biggest_i = i;
				biggest_j = j;
			}
		}
	}
	m->row_end= biggest_i;
	m->column_end = biggest_j;
	m->square_size = biggest_dp;

	m->row_start = m->row_end - m->square_size + 1;
	m->column_start = m->column_end - m->square_size + 1;

}

void	change_matrix(t_matrix* m) {

	for (int i = m->row_start; i <= m->row_end; i++) {
		for (int j = m->column_start; j <= m->column_end; j++) {
			m->matrix[i][j] = m->full;
		}
	}
}

void	free_matrix(char** matrix) {

	for (int i = 0; matrix[i]; i++) {  free(matrix[i]);  }
	free(matrix);
}

void	free_dp(t_matrix m) {

	for (int i = 0; i < m.line_nb; i++) {  free(m.dp[i]);  }
	free(m.dp);
}

//
// DEBUG / VISUALIZATION
//
/*
void	print_matrix(char** matrix) {

	for (int i = 0; matrix[i]; i++) {

		printf("line[%d] is [%s]\n", i, matrix[i]);
	}
}

void	print_dp(t_matrix m) {

	for (int i = 0; i < m.line_nb; i++) {
		printf("line%d: ", i);

		for (int j = 0; j < m.col_nb; j++) {
			printf("[%d]", m.dp[i][j]);
		}
		printf("\n");
	}
}*/
