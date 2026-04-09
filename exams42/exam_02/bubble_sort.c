void	ft_swap(int* tab, unsigned int i, unsigned int j)
{
	int temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

int* sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i = 0;
	unsigned int	j;

	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j+1])
				ft_swap(tab, j, j+1);
			j++;
		}
		i++;
	}
	return (tab);
}

#include <stdio.h>

int	main()
{
	int tab[] = {-34, -999, 0, 87, 11111111, 1};
	unsigned int	size = 5;

	sort_int_tab(tab, 5);
	
	unsigned int	i = 0;
	while (i < size)
	{
		printf("%d\n", tab[i]);
		i++;
	}
}
