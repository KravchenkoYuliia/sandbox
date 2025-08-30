#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_result {

	char**	result;
	int	malloced_size;
} t_result;

void	test(t_result *result)
{

	char *first = strdup("first test");
	result->result = malloc(2 * sizeof(char *));
	result->malloced_size = sizeof(char *) + 1;
	result->result[0] = first;
	result->result[1] = NULL;

	char *second = strdup("second test");
	result->result = realloc(result->result, (result->malloced_size + 1)* sizeof(char *));
	result->result[1] = second;
	result->result[2] = NULL;

}

int	main()
{
	t_result result;

	result.result = NULL;
	result.malloced_size = 0;

	test(&result);
	int	i = 0;
	while (result.result[i])
	{
		printf("line[%d] = %s\n", i, result.result[i]);
		free(result.result[i]);
		i++;
	}
	free(result.result);
}
