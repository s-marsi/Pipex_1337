/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:57:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/17 11:44:03 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		exit(3);
	}
	id = fork();
	if (id < 0)
	{
		perror("fork");
		exit(3);
	}
	if (id == 0)
	{
		dup2(fdp[1], 1);
		close_file(fdp, -1);
		execute_cmd(cmd, env);
	}
	dup2(fdp[0], 0);
	close_file(fdp, -1);
}

static void	foreach_cmds(int ac, char *av[], char *env[])
{
	int	i;
	int	pid;
	int	status;

	i = 2;
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
			exit(WEXITSTATUS(status));
	}
}

int	main(int ac, char *av[], char *env[])
{
	int	fd_in;
	int	fd_out;

	if (ac < 5)
	{
		write(2, "cmd shld be like : ./pipex inFile cmd1 cmd2 outfile\n", 53);
		exit(1);
	}
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (dup2(fd_in, 0) == -1 || dup2(fd_out, 1) == -1)
	{
		perror("Error duplicating file descriptor to (stdin|stdout)");
		exit(1);
	}
	close(fd_in);
	close(fd_out);
	foreach_cmds(ac, av, env);
	return (0);
}
