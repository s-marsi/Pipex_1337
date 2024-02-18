/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:02:33 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/17 18:33:45 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "string.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

void	fork_and_execute(char *cmd[], char *av[], char *envp[]);
char	*get_cmd(char *av, char *path);
char	*get_path(char *envp[]);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	print_str(char *str);
void	close_file(int *fdp, int fd);
void	free_notify(char **str, char *msg);
void	heredoc(int ac, char *av[], char *env[]);
char	*get_next_line(int fd);
char	*read_all(int fd, char *last);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
typedef struct bonus_list
{
	char	*path;
	int		ac;
}	t_list;

#endif