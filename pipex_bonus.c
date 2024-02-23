/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:06 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/23 11:15:40 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	redirect_io(int *fdp)
{
	close(fdp[0]);
	if (dup2(fdp[1], 1) == -1)
	{
		perror("");
		exit(1);
	}
	close(fdp[1]);
}

static void	child1(t_pipex *pipex, char *av[])
{
	int	pid;
	int	fdp[2];

	if (pipe(fdp) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	check_fork(pid);
	if (pid == 0)
	{
		redirect_io(fdp);
		ft_exec(pipex, av);
	}
	if (dup2(fdp[0], 0) == -1)
	{
		perror("");
		exit(1);
	}
	close(fdp[0]);
	close(fdp[1]);
}

static void	child2(t_pipex *pipex, char *av[])
{
	int	pid;
	int	fdp[2];

	if (pipe(fdp) == -1)
	{
		perror("pipe");
		exit(3);
	}
	pid = fork();
	check_fork(pid);
	if (pid == 0)
	{
		close(fdp[0]);
		close(fdp[1]);
		ft_exec(pipex, av);
	}
	close(fdp[0]);
	close(fdp[1]);
}

static void	child_processes(t_pipex *pipex, char *av[], int ac)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd_in == -1 || dup2(fd_in, 0) == -1 || fd_out == -1)
	{
		perror("");
		exit(1);
	}
	close(fd_in);
	while (pipex->index < ac - 1)
	{
		if (pipex->index == ac - 2)
			child2(pipex, av);
		else
		{
			dup2(fd_out, 1);
			close(fd_out);
			child1(pipex, av);
		}
		pipex->index++;
	}
	close(fd_out);
	function_line(NULL);
}

void	pipex_bonus(int ac, char *av[], char *env[])
{
	t_pipex	pipex;

	pipex.index = 2;
	pipex.env = env;
	pipex.path = get_path(env);
	child_processes(&pipex, av, ac);
}
