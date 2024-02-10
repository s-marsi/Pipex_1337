/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/10 19:16:57 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*path;
	char	*cmd[3];

	cmd[2] = NULL;
	path = get_path(envp);
	cmd[0] = get_cmd(av[2], path);
	cmd[1] = get_cmd(av[3], path);
	fork_and_execute(cmd, av, envp);
	return (0);
}
