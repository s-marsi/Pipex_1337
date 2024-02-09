/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/09 18:02:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH"))
		{
			path = ft_strnstr(envp[i], "PATH");
			break ;
		}
		i++;
	}
	path = ft_strnstr(path, "/");
	return (path);
}

char	*get_cmd(char *av, char *path)
{
	char	**split_path;
	char	**cmd;
	char	*cmd_path;
	int		i;

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

	split_cmd = ft_split(av[2], ' ');
	dup2(fdp[1], 1);
	close(fdp[0]);
	close(fdp[1]);
	if (execve(cmd[0], split_cmd, envp) == -1)
	{
		perror("execve error");
		exit(1);
	}
}

void	parent(char *cmd[], char *av[], char *envp[], int *fdp)
{
	char	**split_cmd;
	int		fd;

	split_cmd = ft_split(av[3], ' ');
	fd = open(av[4], O_CREAT | O_RDWR, 0777);
	dup2(fd, 1);
	dup2(fdp[0], 0);
	close(fdp[0]);
	close(fdp[1]);
	if (execve(cmd[1], split_cmd, envp) == -1)
	{
		perror("execve error");
		exit(1);
	}
}

void	execute_cmd(char *cmd[], char *av[], char *envp[])
{
	pid_t	id;
	int		fd;
	int		fdp[2];

	fd = open(av[1], O_RDONLY);
	if (dup2(fd, 0) == -1)
	{
		perror("file not be opened");
		exit(1);
	}
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

int	main(int ac, char *av[], char *envp[])
{
	char	*path;
	char	*cmd[3];

	cmd[2] = NULL;
	path = get_path(envp);
	cmd[0] = get_cmd(av[2], path);
	cmd[1] = get_cmd(av[3], path);
	execute_cmd(cmd, av, envp);
	return (0);
}
