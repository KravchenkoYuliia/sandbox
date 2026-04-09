/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:52:44 by yukravch          #+#    #+#             */
/*   Updated: 2025/12/12 15:47:47 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdbool.h> 

int	len(char* str) {

	if (!str)
		return 0;

	int i = 0;
	while(str[i])
		i++;
	
	return i;
}

char**	life(int row, int col, int iter) {

	char**	matrix = calloc(row, sizeof(char*));
	if (!matrix) {  return NULL;  }

	for (int i = 0; i < row; i++) {  
		matrix[i] = calloc(col, sizeof(char));
		if (!matrix[i]) {  return NULL;  }		
	}
	
	//
	//GETTING THE COMMAND FROM THE STDIN
	//
	char	buffer[1];
	char*	cmd = NULL;
	buffer[0] = '\0';
	int	read_return = -1;
	int	i = 0;
	while (read_return != 0)
	{
		read_return = read(STDIN_FILENO, buffer, 1);
		if (read_return == -1)
			return NULL;
		if (read_return == 0)
			break;
		
		cmd = realloc(cmd, (len(cmd) + 2) * sizeof(char));
		if (!cmd) {  return NULL;  }
		cmd[i] = buffer[0];
		i += 1;
		cmd[i] = '\0';
	}
	
	//
	//WRITING LIFE IN THE MATRIX ACCORDING TO THE CMD
	//
	
	i = 0;
	int	j = 0;
	bool	write = false;
	for (int k = 0; k < len(cmd); k++) {

		if (cmd[k] == 'x') {
			if (write == false) {
				matrix[i][j] = 'O';
				write = true;
			}
			else if (write == true)
				write = false;
		}
		else if (cmd[k] == 'w' && i != 0)
		{
			i -= 1;
			if (write == true)
				matrix[i][j] = 'O';
		}
		else if (cmd[k] == 's' && i < row-1)
		{
			i += 1;
			if (write == true)
				matrix[i][j] = 'O';
		}
		else if (cmd[k] == 'd' && j < col-1)
		{
			j += 1;
			if (write == true)
				matrix[i][j] = 'O';
		}
		else if (cmd[k] == 'a' && j != 0)
		{
			j -= 1;
			if (write == true)
				matrix[i][j] = 'O';
		}
	}
	
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++) {
			if (matrix[i][j] == '\0')
				matrix[i][j] = ' ';
		}
	}
	
	if (iter == 0)
		return matrix;

	//
	//CREATING NEXT GENERATION FOR ITER TIMES
	//
	
	char**	new_gen = calloc(row, sizeof(char*));
	if (!new_gen) {  return NULL;  }

	for (int i = 0; i < row; i++) {  
		new_gen[i] = calloc(col, sizeof(char));
		if (!new_gen[i]) {  return NULL;  }		
	}

	while (iter > 0) {

		//
		//COUNT LIVE NEIGHBORS FOR EVERY CELL
		//
		int count = 0;
		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++) {
				count = 0;	
				if (i != 0 && matrix[i-1][j] == 'O') //up
					count += 1;		
				if (i < row-1 && matrix[i+1][j] == 'O') //down
					count += 1;	
				if (j < col-1 && matrix[i][j+1] == 'O') //right
					count += 1;
				if (j != 0 && matrix[i][j-1] == 'O') //left
					count += 1;
				if (i != 0 && j < col-1 && matrix[i-1][j+1] == 'O') //up-right
					count += 1;		
				if (i != 0 && j != 0 &&  matrix[i-1][j-1] == 'O') //up-left
					count += 1;		
				if (i < row-1 && j < col-1 && matrix[i+1][j+1] == 'O') //down-right
					count += 1;		
				if (i < row-1 && j != 0 && matrix[i+1][j-1] == 'O') //down-left
					count += 1;


				//
				//WRITE NEW GENERATION DEPENDING ON THE PREVIOUS ONE 
				//
				if (matrix[i][j] == ' ') {
					if (count == 3)
						new_gen[i][j] = 'O';
					else
						new_gen[i][j] = ' ';
				}
				else if (matrix[i][j] == 'O') {
					if (count < 2)
						new_gen[i][j] = ' ';
					else if (count == 2 || count == 3)
						new_gen[i][j] = 'O';
					else 
						new_gen[i][j] = ' ';
				}
			}
		}
		iter -= 1;
		if (iter == 0)
			return new_gen;

		//
		//UPDATE MATRIX
		//
		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++) {
				matrix[i][j] = new_gen[i][j];
			}
		}
	}
	return NULL;
}

int	main(int ac, char** av) {


	if (ac != 4)
		return 1;
	int	row = atoi(av[2]);
	int	col = atoi(av[1]);
	int	iter = atoi(av[3]);

	if (row < 1 || col < 1 || iter < 0)
		return 1;
	
	char**	matrix = life(row, col, iter);
	if (!matrix) {  return 1;  }

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {  putchar(matrix[i][j]);  }
		putchar('\n');
	}
	
	return 0;
}
