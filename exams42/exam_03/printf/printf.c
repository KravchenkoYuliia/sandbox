#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char* str)
{
	int i = 0;
	int count = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return count;
}


int	ft_putnbr(int nb)
{
	int count = 0;

	if (nb < 0)
	{
		count += ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	if (nb >= 0 && nb <= 9)
		count += ft_putchar(nb + '0');
	return count;
}

int	ft_count_hexa(unsigned int nb)
{
	int	count = 0;

	while (nb != 0)
	{
		nb /= 16;
		count++;
	}
	return count;
}


int	ft_puthexa(unsigned int nb)
{
	int count = 0;

	if (nb == 0)
	{
		ft_putchar('0');
		return 1;
	}
	count = ft_count_hexa(nb);
	char* base = "0123456789abcdef";
	if (nb > 15)
	{	
		ft_puthexa(nb / 16);
		ft_puthexa(nb % 16);
	}
	else
	{
		ft_putchar(base[nb%16]);
	}
	return (count);
		
}

int	ft_format(char c, va_list args)
{
	int count = 0;

	if (c == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (c == 'd')
		count = ft_putnbr(va_arg(args, int));
	else if (c == 'x')
		count = ft_puthexa(va_arg(args, unsigned int));
	else if (c == '%')
		count = ft_putchar('%');
	return count;
}


int	ft_charset(char c, char* str)
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

int ft_printf(const char *str, ... )
{
	int	count_return = 0;
	int	i = 0;
	va_list	args;

	va_start(args, str);
	if (str == (NULL))
		return -1;
	while (str[i])
	{
		if (str[i] != '%')
			count_return += ft_putchar(str[i]);
		else if (str[i] == '%' && ft_charset(str[i + 1], "sdx%"))
		{	
			count_return += ft_format(str[i + 1], args);
			i++;
		}
		i++;
	}

	va_end(args);
	return count_return;
}

int main(int ac, char** av)
{
	(void) ac;
	
	(void) av;
	int print;
	if (ac < 2)
	{
		printf("Put smth\n");
		exit(EXIT_FAILURE);
	}
	print = ft_printf(NULL);
	printf("Return = %d\n\n\n\n\n\n", print);
	
	
	int ret = 0;
	ret = printf(NULL);
	printf("Return of real printf =  %d\n", ret);
}

