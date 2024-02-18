/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/18 16:34:52 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(char *av[], char *env[], int *fdp, char *path)
{
	char	**cmd;
	char	*path_cmd;
	char	*msg;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
	{
		perror("");
		exit(3);
	}
	close(fdp[0]);
	path_cmd = get_cmd(av[2], path);
	cmd = ft_split(av[2], ' ');
	if (execve(path_cmd, cmd, env) == -1)
	{
		msg = ft_strjoin(cmd[0], " command not found");
		free_notify(cmd, msg);
		free(msg);
		exit(127);
	}
}

static void	child2(char *av[], char *env[], int *fdp, char *path)
{
	char	**cmd;
	char	*path_cmd;
	char	*msg;
	int		fd;

	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1 || dup2(fdp[0], 0) == -1 || dup2(fd, 1) == -1)
	{
		perror("");
		exit(3);
	}
	close(fdp[1]);
	path_cmd = get_cmd(av[3], path);
	cmd = ft_split(av[3], ' ');
	if (execve(path_cmd, cmd, env) == -1)
	{
		msg = ft_strjoin(cmd[0], " command not found");
		free_notify(cmd, msg);
		free(msg);
		exit(127);
	}
}

static void	function_line(int *fdp)
{
	int	status;

	close(fdp[0]);
	close(fdp[1]);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 3)
			exit(WEXITSTATUS(status));
	}
}

static void	pipex(char *av[], char *env[])
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
		if (pid < 0)
			perror("fork");
		if (pid2 == 0)
			child2(av, env, fdp, get_path(env));
	}
	function_line(fdp);
}

int	main(int ac, char *av[], char *env[])
{
	if (ac != 5)
	{
		write(2, "cmd shld be like : ./pipex inFile cmd1 cmd2 outfile\n", 53);
		exit(1);
	}
	else
		pipex(av, env);
	return (0);
}
