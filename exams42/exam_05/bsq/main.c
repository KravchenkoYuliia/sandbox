/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:49:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/12/03 09:49:55 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	main(int ac, char** av) {

	
	if (ac > 2) {
		printf("Error: too much args\n");
		return 1;
	}

	char**	new_matrix = NULL;
	if (ac == 2)
		new_matrix = ft_bsq(av[1]);
	else if (ac == 1)
		new_matrix = ft_bsq(NULL);
	if (!new_matrix){
		printf("Error\n");
		return 1;
	}
	for (int i = 0; new_matrix[i]; i++) {
		printf("%s\n", new_matrix[i]);
	}
	
	free_matrix(new_matrix);
	return 0;
}
