/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:27:20 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/22 14:26:46 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char * str)
{
	int i = 0;
	if (!str)
		return 0;
	while (str[i])
		i++;
	return (i);
}

char* ft_strjoin(char* old_res, char* buffer)
{
	int i = 0;
	int j = 0;
	int len = ft_strlen(old_res) + ft_strlen(buffer) + 1;
	char*	joined_reserve = malloc(sizeof(char) * len);
	if (!joined_reserve)
		return (NULL);

	while (old_res && old_res[i])
	{
		joined_reserve[i] = old_res[i];
		i++;
	}
	free(old_res);
	while (buffer && buffer[j])
	{
		joined_reserve[i] = buffer[j];
		i++;
		j++;
	}
	free(buffer);
	joined_reserve[i] = '\0';
	return (joined_reserve)
}

char*	gnl(int fd)
{
	int		read_return = 1;
	char*		buffer;
	static char* 	reserve;
	char*		line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (read_return > 0)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
		{
			if (reserve)
				free(reserve);
			return (NULL);
		}
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return < 0)
		{
			if (reserve)
				free(reserve);
			free(buffer);
		}
		if (read_return == 0)
		{
			free(buffer);
			break ;
		}
		reserve = ft_strjoin(reserve, buffer);
		if (ft_strchr(reserve, "\n"))
			break ;
	}
	line = ft_cut_line(reserve);
	reserve = ft_update_reserve(reserve, ft_strlen(line));
	return (line);
}

int main()
{
	char* line;

	while (line = gnl(STDIN_FILENO))
	{
		printf("%s\n", line);
		if (line[0] == 'S')
			break ;
		free(line);
	}
}
