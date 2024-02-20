/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:57:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/20 16:31:15 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc(int ac, char *av[], char *env[])
{
	int		fd_out;
	int		fdp[2];

	if (pipe(fdp) == -1)
	{
		perror("pipe");
		exit(1);
	}
	read_content(fdp, av);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (dup2(fdp[0], 0) == -1 || dup2(fd_out, 1) == -1)
	{
		perror("Error duplicating file descriptor to (stdin|stdout)");
		exit(1);
	}
	close_file(fdp, fd_out);
	foreach_cmds(ac, av, env);
}

int	main(int ac, char *av[], char *env[])
{
	if (ac < 5)
	{
		write(2, "cmd shld be like : ./pipex inFile cmd1 cmd2 outfile\n", 53);
		exit(1);
	}
	else if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		heredoc(ac, av, env);
	else
		pipex_bonus(ac, av, env);
	return (0);
}
