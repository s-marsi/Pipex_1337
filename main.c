/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/08 12:01:13 by smarsi           ###   ########.fr       */
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
			break;
		}
		i++;
	}
	return (cmd_path);
}

void	execute_cmd(char *cmd, char *av[], char *env[])
{
	char	*infile;
	char	*args[];

	infile = av[1];
	args = {av[2], av[1], NULL};
	if (execve(cmd, args, envp) == -1)
		perror("");
}

int	main(int ac, char *av[], char *envp[])
{
	char	*path;
	char	*cmd;

	path = get_path(envp);
	cmd = get_cmd(av[2], path);
	execute_cmd(cmd, av, envp);
	return (0);
}
