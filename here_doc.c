/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:35:04 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/21 14:53:49 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	put_str(char *str, int fd)
{
	if (str)
	{
		while (*str)
		{
			write(fd, str, 1);
			str++;
		}
	}
	
}

static void	execute_cmd(char *cmd, char *env[])
{
	char	*msg;
	char	*path;
	char	**split_cmd;
	char	*cmd_path;

	path = get_path(env);
	cmd_path = get_cmd(cmd, path);
	split_cmd = ft_split(cmd, ' ');
	if (execve(cmd_path, split_cmd, env) == -1)
	{
		msg = ft_strjoin(split_cmd[0], " command not found");
		free_notify(split_cmd, msg);
		free(msg);
		free(cmd_path);
		exit(127);
	}
}

static void	pipe_redirect(char *cmd, char *env[])
{
	int		id;
	int		fdp[2];

	if (pipe(fdp) != 0)
	{
		perror("pipe");
		exit(1);
	}
	id = fork();
	if (id < 0)
	{
		perror("fork");
		exit(1);
	}
	if (id == 0)
	{
		dup_file(fdp[1], 1);
		close_file(fdp, -1);
		execute_cmd(cmd, env);
	}
	dup_file(fdp[0], 0);
	close_file(fdp, -1);
}

void	foreach_cmds(int ac, char *av[], char *env[])
{
	int	i;
	int	pid;
	int	status;

	i = 3;
	while (i < ac - 2)
		pipe_redirect(av[i++], env);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		exit(10);
	}
	if (pid == 0)
		execute_cmd(av[ac - 2], env);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
		{
			system("leaks pipex_bonus");
			exit(WEXITSTATUS(status));
		}
	}
}

void	read_content(int *fdp, char **av)
{
	char	*buf;
	char	*delimiter;

	buf = NULL;
	while (1)
	{
		write(1, "heredoc> ", 9);
		delimiter = ft_strjoin(av[2], "\n");
		buf = get_next_line(0);
		if (!buf || !ft_strcmp(buf, delimiter))
		{
			free(delimiter);
			free(buf);
			break ;
		}
		put_str(buf, fdp[1]);
		free(delimiter);
		free(buf);
	}
}
