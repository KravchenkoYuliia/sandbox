#include <unistd.h>

int	ft_check_double(char *str, char c, int i)
{
	i--;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i--;
	}
	return (0);
}

int	ft_charset(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 3)
	{
		write(1, &av[1][i], 1);
		i++;
		while (av[1][i])
		{
			if (!ft_check_double(av[1], av[1][i], i))
			{
				write(1, &av[1][i], 1);
			}
			i++;
		}
		i = 0;
		while (av[2][i])
		{
			if (!ft_charset(av[1], av[2][i]) && !ft_check_double(av[2], av[2][i], i))
			{	
				write(1, &av[2][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
