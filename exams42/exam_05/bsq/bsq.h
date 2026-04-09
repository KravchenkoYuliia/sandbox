/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:54:57 by yukravch          #+#    #+#             */
/*   Updated: 2025/12/09 13:57:45 by yukravch         ###   ########.fr       */
/* ************************************************************************** */

#ifndef BSQ_H
#define BSQ_H

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct s_matrix {

	char*	header;
	char**	matrix;
	int**	dp;

	int	row_start;
	int	column_start;
	int	row_end;
	int	column_end;
	int	square_size;

	int	line_nb;
	int	col_nb;

	char	empty;
	char	obstacle;
	char	full;

} t_matrix;

char**	ft_bsq(char* stream);
int	ft_getline(FILE* stream, t_matrix* m);
int	get_matrix(char* stream, t_matrix* m);
void	init_m(t_matrix* m);
int	fill_struct(t_matrix* m, char* stream);
bool    error_in_parsing(t_matrix m);
void	dp( t_matrix* m );
void    get_coordinate_of_square(t_matrix* m);
void    change_matrix(t_matrix* m);

void	print_matrix(char** matrix);
void	print_dp(t_matrix m);

char*	ft_strdup(char* buffer);
int	ft_min(int a, int b, int c);

void	free_matrix(char** matrix);
void	free_dp(t_matrix m);
#endif
