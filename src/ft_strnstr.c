/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:39:26 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/19 15:29:56 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!haystack && needle)
		return (NULL);
	if (!*needle)
		return ((char *) haystack);
	i = -1;
	while (haystack[++i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] && haystack[i + j] == needle[j])
				j++;
			if (!needle[j])
				return ((char *) haystack + i);
		}
	}
	return (NULL);
}
