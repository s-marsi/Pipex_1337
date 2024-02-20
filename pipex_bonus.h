/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:09:48 by smarsi            #+#    #+#             */
/*   Updated: 2024/02/20 16:29:44 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

void	pipex_bonus(int ac, char *av[], char *env[]);
void	check_fork(int pid);
void	foreach_cmds(int ac, char *av[], char *env[]);
void	read_content(int *fdp, char **av);
void	function_line(int *fdp);
char	*get_cmd(char *av, char *path);
char	*get_path(char *envp[]);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	close_file(int *fdp, int fd);
void	free_notify(char **str, char *msg);
void	heredoc(int ac, char *av[], char *env[]);
char	*get_next_line(int fd);
char	*read_all(int fd, char *last);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
typedef struct bonus_list
{
	int		index;
	char	**env;
	char	*path;
}	t_pipex;
void	ft_exec(t_pipex *pipex, char *av[]);

#endif