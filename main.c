/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/15 16:15:10 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*path;
	int		status;
	char	*cmd[3];

	if (ac != 5)
	{
		write(2, "cmd shld be like : ./pipex inFile cmd1 cmd2 outfile", 52);
		exit(1);
	}
	cmd[2] = NULL;
	path = get_path(envp);
	cmd[0] = get_cmd(av[2], path);
	cmd[1] = get_cmd(av[3], path);
	fork_and_execute(cmd, av, envp);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
			exit(WEXITSTATUS(status));
	}
	return (0);
}
