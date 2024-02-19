/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:07:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/19 16:24:41 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	redirect_io(t_pipex *pipex, char *av[], int *fdp)
{
	int		fd;

	if (pipex->index == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1 || dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
		{
			perror("");
			exit(3);
		}
	}
	else
	{
		if (dup2(fdp[0], 0) == -1 || dup2(fdp[1], 1) == -1)
		{
			perror("");
			exit(3);
		}
	}
	close(fdp[0]);
}

static void	child1(t_pipex *pipex, char *av[], int *fdp)
{
	char	**cmd;
	char	*path_cmd;
	char	*msg;

	redirect_io(pipex, av, fdp);
	path_cmd = get_cmd(av[pipex->index], pipex->path);
	cmd = ft_split(av[pipex->index], ' ');
	if (execve(path_cmd, cmd, pipex->env) == -1)
	{
		msg = ft_strjoin(cmd[0], " command not found");
		free_notify(cmd, msg);
		free(msg);
		exit(127);
	}
}

static void	child2(t_pipex *pipex, char *av[], int *fdp)
{
	char	**cmd;
	char	*path_cmd;
	char	*msg;
	int		fd;

	fd = open(av[pipex->index + 1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1 || dup2(fdp[0], 0) == -1 || dup2(fd, 1) == -1)
	{
		perror("");
		exit(3);
	}
	close(fdp[1]);
	path_cmd = get_cmd(av[pipex->index], pipex->path);
	cmd = ft_split(av[pipex->index + 1], ' ');
	if (execve(path_cmd, cmd, pipex->env) == -1)
	{
		msg = ft_strjoin(cmd[0], " command not found");
		free_notify(cmd, msg);
		free(msg);
		exit(127);
	}
}

static void	child_processes(t_pipex *pipex, char *av[], int *fdp, int ac)
{
	int	pid;
	int	pid2;

	pid = fork();
	check_fork(pid);
	if (pid == 0)
	{
		while (pipex->index < ac - 2)
		{
			child1(pipex, av, fdp);
			pipex->index++;
		}
	}
	else
	{
		pid2 = fork();
		if (pid < 0)
			perror("fork");
		if (pid2 == 0)
		{
			pipex->index = ac - 2;
			child2(pipex, av, fdp);
		}
	}
}

void	pipex_bonus(int ac, char *av[], char *env[])
{
	int		fdp[2];
	t_pipex	pipex;

	pipex.index = 2;
	pipex.env = env;
	pipex.path = get_path(env);
	if (pipe(fdp) < 0)
		perror("pipe");
	child_processes(&pipex, av, fdp, ac);
	function_line(fdp);
}
