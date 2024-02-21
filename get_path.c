/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:22:35 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/21 09:05:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strjoin_with_slash(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(len * sizeof(char));
	if (!str)
		return (str);
	str[0] = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, "/", ft_strlen(s1) + 2);
	ft_strlcat(str, s2, len + 1);
	return (str);
}

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
			tmp = ft_strjoin_with_slash(*split_path, cmd);
			if (access(tmp, X_OK) == 0)
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

	cmd_path = NULL;
	split_path = NULL;
	if (path)
		split_path = ft_split(path, ':');
	cmd = ft_split(av, ' ');
	if (access(cmd[0], X_OK) == 0 && (cmd[0][0] == '/'
		|| (cmd[0][0] == '.' && cmd[0][1] == '/')))
		cmd_path = ft_strdup(cmd[0]);
	else if (split_path)
		cmd_path = path_cmd(split_path, cmd[0]);
	ft_free(split_path, cmd);
	return (cmd_path);
}
