#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

int	ft_strlen(char* s)
{
	int i = 0;

	if (!s)
		return 0;
	while (s[i])
		i++;
	return i;
}

void	ft_error(char *msg, char *cmd)
{
	write(2, msg, ft_strlen(msg));
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	ft_cd(char **av, int start, int stop)
{
	int	i = 0;

	if (!av[start+1] || stop > start +2)
	{
		ft_error("error: cd: bad arguments", NULL);
		return ;
	}
	if (chdir(av[start+1]) != 0)
	{
		ft_error("error: cd: cannot change directory to ", av[start+1]);
		return ;
	}
}

void	ft_fork(pid_t* pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_error("error: fatal", NULL);
		exit(EXIT_FAILURE);
	}
}

void	ft_exec_child(int cmd_start, int cmd_end, char** av, char** env)
{
	char*	temp = av[cmd_end];

	av[cmd_end] = NULL;
	execve(av[cmd_start], &av[cmd_start], env);
}

void	ft_pipe(char** av, int start, int stop, char** env)
{
	int	i = start;
	int	cmd_start = i;
	int	cmd_end;
	
	pid_t	pid;
	int	init[2];
	int	save_stdin = dup(STDIN_FILENO);

	while (i < stop && av[i])
	{
		if (av[i][0] == '|')
		{
			if (pipe(init) == -1)
			{
				ft_error("error: fatal", NULL);
				exit(EXIT_FAILURE);
			}
			
			cmd_end = i;
			ft_fork(&pid);
			if (pid == 0)
			{
				close(save_stdin);
				close(init[0]);
				dup2(init[1], STDOUT_FILENO);
				close(init[1]);
				ft_exec_child(cmd_start, cmd_end, av, env);
			}

			dup2(init[0], STDIN_FILENO);
			close(init[1]);
			close(init[0]);
			cmd_start = i + 1;
		}
		i++;
	}
	if (cmd_start < stop)
	{
		cmd_end = stop;
		ft_fork(&pid);
		if (pid == 0)
		{
			close(save_stdin);
			ft_exec_child(cmd_start, cmd_end, av, env);
		}
	}
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
}

void	ft_one_cmd(char** av, int start, int stop, char** env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error("error: fatal", NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char	*temp = av[stop];

		av[stop] = NULL;
		if (execve(av[start], &av[start], env) == -1)
		{
			av[stop] = temp;
			printf("FAIL\n");
			ft_error("error: cannot execute", av[start]);
			return ;
		}
	}
	waitpid(pid, NULL, 0);
}

void	ft_exec(char** av, int start, int stop, bool pipe, char** env)
{
	int	i = start;

	if (!pipe)
	{
		if (strcmp(av[start], "cd") == 0)
			ft_cd(av, start, stop);
		else
			ft_one_cmd(av, start, stop, env);
	}
	else
		ft_pipe(av, start, stop, env);
}

void	ft_micro(int ac, char** av, char** env)
{
	int	i = 0;
	int	start = 0;
	bool	pipe = false;

	while (av[i])
	{
		if (av[i][0] == '|')
			pipe = true;
		if (av[i][0] == ';')
		{
			ft_exec(av, start, i, pipe, env);
			start = i + 1;
			pipe = false;
		}
		i++;
	}
	if (start < i)
		ft_exec(av, start, i, pipe, env);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
		return (1);
	ft_micro(ac, av + 1, env);
}
