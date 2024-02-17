/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:22:35 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/17 11:43:00 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **str, char **str2)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			free(str[i++]);
	i = 0;
	if (str2)
		while (str2[i])
			free(str2[i++]);
	free(str);
	free(str2);
}

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

static char	*path_cmd(char **split_path, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	cmd_path = NULL;
	if (split_path)
	{
		while (*split_path)
		{
			tmp = ft_strjoin(*split_path, cmd);
			if (access(tmp, F_OK & X_OK) == 0)
			{
				cmd_path = tmp;
				break ;
			}
			free(tmp);
			split_path++;
		}
	}
	return (cmd_path);
}

char	*get_cmd(char *av, char *path)
{
	char	**split_path;
	char	**cmd;
	char	*cmd_path;
	char	*tmp;

	cmd_path = NULL;
	split_path = NULL;
	if (path)
		split_path = ft_split(path, ':');
	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK & X_OK) == 0)
		cmd_path = ft_strdup(cmd[0]);
	else if (split_path)
		cmd_path = path_cmd(split_path, cmd[0]);
	ft_free(split_path, cmd);
	return (cmd_path);
}
