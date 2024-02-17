/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:39:22 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/17 11:57:37 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_file(int *fdp, int fd)
{
	close(fdp[0]);
	close(fdp[1]);
	if (fd >= 0)
		close(fd);
}

void	free_notify(char **str, char *msg)
{
	int	i;

	if (msg)
		perror(msg);
	i = 0;
	if (str)
		while (str[i])
			free(str[i++]);
}
