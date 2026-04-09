#include <stdio.h>
#include <unistd.h>

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char new = 0;
	int	i_octet = 7;
	int	i_new = 0;

	while (i_octet >= 0)
	{
		if (octet & (1 << i_octet))
		{
			new = (new | (1 << i_new)); 
			printf("%d %d\n", i_octet, i_new);
			//write(1, "1", 1);
		}
			//write(1, "0", 1);
		i_octet--;
		i_new++;
	}
	return new;
}

#include <stdlib.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	int octet = atoi(av[1]);
	printf("%8b\n", octet);

	unsigned char result = reverse_bits(octet);
	printf("%16b\n", result);
	//printf("%08b\n", result);
}
