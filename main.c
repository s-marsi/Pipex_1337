/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/07 19:41:20 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle);

char *getPath(char *envp[])
{
	int	i;
	char *path;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i] ,"PATH"))
		{
			path = ft_strnstr(envp[i] ,"PATH");
			break;
		}
		i++;
	}
	path = ft_strnstr(path, "/");
	return (path);
}

char *getCmd(char *av, char *path)
{
	char **split_path;

	split_path = ft_split(av, ':');
	int i = 0;
	printf("This is PATH : %s\n", path);
	// while (split_path[i])
	// {
		printf("%s \n", split_path[0]);
	// }
	return ("test");
}

int	main(int ac, char *av[], char *envp[])
{
	char	*infile = av[1];
	char	*args[] = {av[2], av[3], av[1], NULL};
	char	*path;
	char	*cmd;

	path = getPath(envp);
	cmd = getCmd(av[2], path);
	// execve("/bin/ls", args, envp);
	return (0);
}
