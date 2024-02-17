/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:16:47 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/17 11:58:48 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(char *cmd[], char *av[], char *envp[], int *fdp)
{
	char	**split_cmd;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
	{
		if (fd == -1)
			free_notify(cmd, "File1");
		else
			free_notify(cmd, "Error duplicating fd to (stdin|stdout)");
		exit(1);
	}
	split_cmd = ft_split(av[2], ' ');
	close_file(fdp, fd);
	if (execve(cmd[0], split_cmd, envp) == -1)
	{
		free_notify(cmd, "command 1 not found");
		exit(127);
	}
}

static void	parent(char *cmd[], char *av[], char *envp[], int *fdp)
{
	char	**split_cmd;
	int		fd;

	split_cmd = ft_split(av[3], ' ');
	fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1 || dup2(fd, 1) == -1 || dup2(fdp[0], 0) == -1)
	{
		if (fd == -1)
			free_notify(cmd, "Error when create File2");
		else
			free_notify(cmd, "Error duplicating fd to (stdin|stdout)");
		exit(2);
	}
	close_file(fdp, fd);
	if (execve(cmd[1], split_cmd, envp) == -1)
	{
		free_notify(cmd, "command 2 not found");
		exit(127);
	}
}

void	fork_and_execute(char *cmd[], char *av[], char *envp[])
{
	pid_t	id;
	pid_t	id2;
	int		fdp[2];

	if (pipe(fdp) != 0)
		perror("pipe");
	id = fork();
	if (id == -1)
		perror("fork");
	else
	{
		if (id == 0)
			child(cmd, av, envp, fdp);
		else
		{
			id2 = fork();
			if (id2 == 0)
				parent(cmd, av, envp, fdp);
		}
	}
	close(fdp[0]);
	close(fdp[1]);
}
