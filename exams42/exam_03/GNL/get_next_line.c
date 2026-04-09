#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

//#define BUFFER_SIZE 10


int	ft_strlen(char* str)
{
	int i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char* ft_strjoin(char* reserve, char* buffer)
{
	char* full;
	int	i = 0;
	int 	j = 0;
	int	len = ft_strlen(reserve) + ft_strlen(buffer) + 1;

	full = malloc(sizeof(char) * len);
	if (!full)
	{
	      	free(reserve);
		free(buffer);
		return (NULL);
	}
	while (reserve && reserve[i])
	{
		full[i] = reserve[i];
		i++;
	}
	free(reserve);
	reserve = NULL;
	while (buffer[j])
	{
		full[i] = buffer[j];
		i++;
		j++;
	}
	full[i] = '\0';
	free(buffer);
	return (full);
}

int	ft_strchr(char* str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_len_line(char* str)
{
	int	i = 0;

	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char*	ft_cut_line(char* reserve)
{
	char* line = NULL;
	int i = 0;

	line = malloc(sizeof(char) * ft_len_line(reserve) + 1);
	if (!line)
	{
		free(reserve);
		return (NULL);
	}
	while (reserve[i] && reserve[i] != '\n')
	{
		line[i] = reserve[i];
		i++;
	}
	if (reserve[i] == '\n')
	{
		line[i] = reserve[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char*	ft_update_reserve(char* old_res, int start)
{
	char* reserve;

	int temp = start;
	int	len = 0;
	while (old_res[temp])
	{
		len++;
		temp++;
	}
	reserve = malloc(sizeof(char) * len + 1);
	if (!reserve)
	{
		free(old_res);
		return (NULL);
	}
	int i = 0;
	while (old_res[start])
	{
		reserve[i] = old_res[start];
		start++;
		i++;
	}
	free(old_res);
	reserve[i] = '\0';
	if (reserve[0] == '\0')
	{
		free(reserve);
		reserve = NULL;
		return (NULL);
	}
	return (reserve);
}

char* get_next_line(int fd)
{
	char* buffer = NULL;
	static char* reserve = NULL;
	char* line;
	int	read_ret = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (read_ret > 0)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret < 0)
		{
			if (reserve)
			{
				free(reserve);
				reserve = NULL;
			}
				
			free(buffer);
			return (NULL);
		}
		if (read_ret == 0)
		{
			free(buffer);
			break ;
		}
		buffer[read_ret] = '\0';
		reserve = ft_strjoin(reserve, buffer);
		if (reserve == NULL)
			return (NULL);
		if (ft_strchr(reserve, '\n'))
			break ;
	}
	if (!reserve)
		return (NULL);
	line = ft_cut_line(reserve);
	if (line == NULL)
		return (NULL);
	reserve = ft_update_reserve(reserve, ft_strlen(line));
	return (line);
}
/*
 #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
int     main(int ac, char **av)
{
        (void)ac;
//        (void)av;
        int   fd = open(av[1], O_RDONLY);

        char* line;
       while ((line = get_next_line(fd)))
        {
                printf("%s", line);
                if (line[0] == 'S')
                {
                        free(line);
                        break ;
                }
                free(line);
        }
}*/
