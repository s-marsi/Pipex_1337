/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:57:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/16 18:29:13 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_file(int *fdp, int fd)
{
	close(fdp[0]);
	close(fdp[1]);
	// close(fd);
}

static void	ft_free(char **str, char *msg)
{
	int	i;

	if (msg)
		perror(msg);
	i = 0;
	while (str[i])
		free(str[i++]);
}

static void	execute_cmd(char *cmd_path, char *split_cmd[], char *env[])
{
	char	*msg;

	if (execve(cmd_path, split_cmd, env) == -1)
	{
		msg = ft_strjoin(split_cmd[0], " command not found");
		ft_free(split_cmd, msg);
		free(msg);
		exit(127);
	}
}

static void	get_cmnd(char *cmd, char *path, char *env[])
{
	char	*cmd_path;
	char	**split_cmd;
	int		id;
	int		fdp[2];
	char *buf =malloc(100);
	cmd_path = get_cmd(cmd, path);
	split_cmd = ft_split(cmd, ' ');
	id = fork();
	if (id == -1 || pipe(fdp) != 0)
	{
		if (id == -1)
			perror("fork");
		else
			perror("pipe");
		exit(3);
	}
	if (id == 0)
	{
		read(fdp[0], buf, 80);
		buf[80] = 0;
		printf("this : %s\n", buf);
		dup2(fdp[1], 1);
		close_file(fdp, -1);
		execute_cmd(cmd_path, split_cmd, env);
	}
	dup2(fdp[0], 0);
	close_file(fdp, -1);
}

static void	foreach_cmds(int ac, char *av[], char *env[])
{
	char	*path;
	char	**split_cmd;
	char	*cmd_path;
	int		i;
	int pid;
	int s;
	path = get_path(env);
	i = 2;
	while (i < ac - 2)
	{
		get_cmnd(av[i], path, env);
		i++;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		exit(10);
	}
	if (!pid)
	{
		cmd_path = get_cmd(av[i], path);
	split_cmd = ft_split(av[i], ' ');
	execute_cmd(cmd_path, split_cmd, env);
	}
	while (wait(&s) != -1)
	{
		if (s != 0)
			exit(s);
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
	foreach_cmds(ac, av, env);
	close(fd_in);
	return (0);
}
