/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:19:10 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/19 16:15:22 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

char	*read_all(int fd, char *last)
{
	char	*buf;
	int		size;

	buf = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free(last), NULL);
	size = 1;
	while (!ft_strchr(last, '\n') && size)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
		{
			free(buf);
			free(last);
			return (NULL);
		}
		buf[size] = '\0';
		last = ft_strjoin(last, buf);
	}
	free(buf);
	return (last);
}
