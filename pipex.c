/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:16:47 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/10 19:18:12 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH"))
		{
			path = ft_strnstr(envp[i], "PATH");
			break ;
		}
		i++;
	}
	if (path)
		path = ft_strnstr(path, "/");
	return (path);
}

char	*get_cmd(char *av, char *path)
{
	char	**split_path;
	char	**cmd;
	char	*cmd_path;
	int		i;

	if (!path)
		return (NULL);
	cmd_path = NULL;
	split_path = ft_split(path, ':');
	cmd = ft_split(av, ' ');
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		if (access(ft_strjoin(split_path[i], cmd[0]), X_OK) == 0)
		{
			cmd_path = ft_strjoin(split_path[i], cmd[0]);
			break ;
		}
		i++;
	}
	return (cmd_path);
}

void	child(char *cmd[], char *av[], char *envp[], int *fdp)
{
	char	**spc_cmd;
	char	**split_cmd;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("File1");
		exit(1);
	}
	if (dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
	{
		perror("Error duplicating file descriptor to (stdin|stdout)");
		exit(1);
	}
	split_cmd = ft_split(av[2], ' ');
	close(fdp[0]);
	close(fdp[1]);
	if (execve(cmd[0], split_cmd, envp) == -1)
	{
		perror("command 1 not found");
		exit(1);
	}
}

void	parent(char *cmd[], char *av[], char *envp[], int *fdp)
{
	char	**split_cmd;
	int		fd;

	split_cmd = ft_split(av[3], ' ');
	fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error when create File2");
		exit(2);
	}
	if (dup2(fd, 1) == -1 || dup2(fdp[0], 0) == -1)
	{
		perror("Error duplicating file descriptor to (stdin|stdout)");
		exit(1);
	}
	close(fdp[0]);
	close(fdp[1]);
	if (execve(cmd[1], split_cmd, envp) == -1)
	{
		perror("command 2 not found");
		exit(1);
	}
}

void	fork_and_execute(char *cmd[], char *av[], char *envp[])
{
	pid_t	id;
	int		fd;
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
			wait(NULL);
			parent(cmd, av, envp, fdp);
		}
	}
}
