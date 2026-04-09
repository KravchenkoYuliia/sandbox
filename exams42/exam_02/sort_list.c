#include "list.h"

int	ft_check(int i, int j)
{
	if (i > j)
		return (0);
	return 1;
}
t_list*	sort_list(t_list* lst, int (*cmp)(int, int))
{
	int	i = 0;
	t_list*	tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if ((cmp)(lst->data, lst->next->data) == 0)
		{
			i = lst->data;
			lst->data = lst->next->data;
			lst->next->data = i;

			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

#include <stdio.h>

int	main()
{
	t_list* test;

	test->data = 4;
	test->next->data = 0;
	printf("before: %d  %d", test->data, test->next->data);


	test = sort_list(test, ft_check);
	printf("after: %d  %d", test->data, test->next->data);
}
