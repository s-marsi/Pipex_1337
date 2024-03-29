/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:07:11 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/23 11:07:42 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec(char *av, char *env[], char *path)
{
	char	**cmd;
	char	*path_cmd;
	char	*msg;

	if (av[0] == '\0')
		cmd = ft_split("cat", ' ');
	else
		cmd = ft_split(av, ' ');
	path_cmd = get_cmd(cmd[0], path);
	if (execve(path_cmd, cmd, env) == -1)
	{
		msg = ft_strjoin(cmd[0], " command not found");
		free_notify(cmd, msg);
		free(msg);
		free(path_cmd);
		exit(127);
	}
}

static void	child1(char *av[], char *env[], int *fdp, char *path)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
	{
		if (fd == -1)
			free_notify(NULL, av[1]);
		else
			perror("");
		exit(1);
	}
	close(fdp[0]);
	ft_exec(av[2], env, path);
}

static void	child2(char *av[], char *env[], int *fdp, char *path)
{
	int		fd;

	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1 || dup2(fdp[0], 0) == -1 || dup2(fd, 1) == -1)
	{
		if (fd == -1)
			free_notify(NULL, av[4]);
		else
			perror("");
		exit(1);
	}
	close(fdp[1]);
	ft_exec(av[3], env, path);
}

void	pipex(char *av[], char *env[])
{
	int	pid;
	int	pid2;
	int	fdp[2];

	if (pipe(fdp) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(3);
	}
	if (pid == 0)
		child1(av, env, fdp, get_path(env));
	else
	{
		pid2 = fork();
		check_fork(pid2);
		if (pid2 == 0)
			child2(av, env, fdp, get_path(env));
	}
	function_line(fdp);
}
