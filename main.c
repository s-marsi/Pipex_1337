/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/18 15:18:44 by smarsi           ###   ########.fr       */
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

static void	pipe_redirect(char *cmd, char *env[], int fd_in)
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
		close(fdp[0]);
		dup2(fdp[1], 1);
		execute_cmd(cmd, env);
	}
	dup2(fdp[0], 0);
	close(fdp[0]);
	close(fdp[1]);
}

static void	foreach_cmds(char *av[], char *env[], int fd_in)
{
	int	pid;
	int	status;

	pipe_redirect(av[2], env, fd_in);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		exit(10);
	}
	if (pid == 0)
		execute_cmd(av[3], env);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 3)
			exit(WEXITSTATUS(status));
	}
}

static void	handle_io_files(char *av[], char *env[], int ac)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_in == -1 || fd_out == -1)
	{
		if (fd_in == -1)
			perror("Infile Not found");
		if (fd_out == -1)
			perror("Error creating outfile");
		exit(1);
	}
	if (dup2(fd_in, 0) == -1 || dup2(fd_out, 1) == -1)
	{
		perror("Error duplicating file descriptor to (stdin|stdout)");
		exit(1);
	}
	close(fd_in);
	close(fd_out);
	foreach_cmds(av, env, fd_in);
}

int	main(int ac, char *av[], char *env[])
{
	if (ac != 5)
	{
		write(2, "cmd shld be like : ./pipex inFile cmd1 cmd2 outfile\n", 53);
		exit(1);
	}
	else
		handle_io_files(av, env, ac);
	return (0);
}
