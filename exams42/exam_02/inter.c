#include <unistd.h>

int	ft_same_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_double(char *str, char c, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 3)
	{
		while (av[1][i])
		{
			if (ft_same_char(av[1][i], av[2]) && !ft_check_double(av[1], av[1][i], i-1))
				write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
