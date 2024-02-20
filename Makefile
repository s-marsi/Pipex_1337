CFLAGS = -Wall -Wextra -Werror

CC = cc


NAME = pipex

NAME_BONUS = pipex_bonus

FILES = src/ft_split.c src/ft_strlcpy.c src/ft_strnstr.c src/ft_strjoin.c src/ft_strncmp.c get_path.c helpers.c pipex.c  main.c

BONUS_FILES = src/ft_split.c src/ft_strlcpy.c src/ft_strnstr.c src/ft_strjoin.c src/ft_strncmp.c get_path.c helpers.c here_doc.c src/get_next_line.c src/get_next_line_utils.c pipex_bonus.c main_bonus.c

FILES_O = $(FILES:.c=.o)

BONUS_O = $(BONUS_FILES:.c=.o)

$(NAME) : $(FILES_O)
	cc $(CFLAGS) $? -o $@

$(NAME_BONUS) : $(BONUS_O)
	cc $(CFLAGS) $? -o $@

all : $(NAME) $(NAME_BONUS)

bonus : $(NAME_BONUS)

clean :
	rm -f $(FILES_O) $(BONUS_O)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY : clean fclean