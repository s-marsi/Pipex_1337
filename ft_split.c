/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:00:28 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/07 19:15:00 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dstsize > 0)
	{
		while (*src && dstsize-- > 1)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (len_src);
}

static	void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static	int	count_word(char const *s, char c)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && flag)
		{
			count++;
			flag = 0;
		}
		if (s[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

static	char	*get_word(char *dst, char const *src, char c, int	*index)
{
	int	i;
	int	start;
	int	len;

	i = *index;
	while (src[i] && src[i] == c)
		i++;
	start = i;
	while (src[i] && src[i] != c)
		i++;
	len = (i - start) + 1;
	dst = malloc((len + 1) * sizeof(char));
    if (!dst)
        return (NULL);
    dst[len] = '\0';
	ft_strlcpy(dst, src + start, len);
	*index = i;
	return (dst);
}

static char	**fill_array(char **dst, char const *src, char c, int number_word)
{
	int	i;
	int	index_word;

	index_word = 0;
	i = 0;
	while (i < number_word)
	{
		dst[i] = get_word(dst[i], src, c, &index_word);
		if (!dst[i])
			ft_free(dst);
		i++;
	}
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	dst = malloc((count + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
    dst[count] = NULL;
	dst = fill_array(dst, s, c, count);
	return (dst);
}