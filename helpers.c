/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:39:22 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/20 18:49:05 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_fork(int pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(3);
	}
}

void	function_line(int *fdp)
{
	int	status;

	if (fdp)
	{
		close(fdp[0]);
		close(fdp[1]);
	}
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
			exit(WEXITSTATUS(status));
	}
}

void	close_file(int *fdp, int fd)
{
	close(fdp[0]);
	close(fdp[1]);
	if (fd >= 0)
		close(fd);
}

void	free_notify(char **str, char *msg)
{
	int	i;

	if (msg)
		perror(msg);
	i = 0;
	if (str)
		while (str[i])
			free(str[i++]);
	free(str);
}

void	ft_exec(t_pipex *pipex, char *av[])
{
	char	*msg;
	char	*path_cmd;
	char	**cmd;

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
