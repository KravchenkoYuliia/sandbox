/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:20:22 by yukravch          #+#    #+#             */
/*   Updated: 2025/12/08 17:20:22 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char*	ft_strdup(char* buffer) {

	size_t	len = strlen(buffer);


	char*	line = NULL;
	if (buffer[len-1] == '\n')
		line = calloc(sizeof(char), len);
	else
		line = calloc(sizeof(char), len + 1);
	size_t i = 0; 
	while (i < len && buffer[i] != '\n') {
	
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return line;
}

int	ft_min(int a, int b, int c) {

	int	min = a;
	if (b < min)
		min= b;
	if (c < min)
		min = c;
	return min;
}
