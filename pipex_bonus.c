/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:17:40 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/15 16:22:23 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.c"

static void	ft_free(char **str, char *msg)
{
	int	i;

	perror(msg);
	i = 0;
	while (str[i])
		free(str[i++]);
}

static void	close_file(int *fdp, int fd)
{
	close(fdp[0]);
	close(fdp[1]);
	close(fd);
}

static void	child(char *cmd[], char *av[], char *envp[], int *fdp)
{
	char	**split_cmd;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
	{
		if (fd == -1)
			ft_free(cmd, "File1");
		else
			ft_free(cmd, "Error duplicating file descriptor to (stdin|stdout)");
		exit(1);
	}
	split_cmd = ft_split(av[2], ' ');
	close_file(fdp, fd);
	if (execve(cmd[0], split_cmd, envp) == -1)
	{
		ft_free(cmd, "command 1 not found");
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
			ft_free(cmd, "Error when create File2");
		else
			ft_free(cmd, "Error duplicating file descriptor to (stdin|stdout)");
		exit(2);
	}
	close_file(fdp, fd);
	if (execve(cmd[1], split_cmd, envp) == -1)
	{
		ft_free(cmd, "command 2 not found");
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
