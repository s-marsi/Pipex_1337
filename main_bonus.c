/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:57:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/19 16:14:21 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
