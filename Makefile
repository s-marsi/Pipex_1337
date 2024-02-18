CFLAGS = -Wall -Wextra -Werror

CC = cc

AR = ar -r

NAME = pipex
NAME_BONUS = pipex_bonus


FILES = ft_split.c ft_strlcpy.c ft_strnstr.c ft_strjoin.c ft_strncmp.c get_path.c helpers.c  main.c

BONUS_FILES = ft_split.c ft_strlcpy.c ft_strnstr.c ft_strjoin.c ft_strncmp.c get_path.c helpers.c here_doc.c get_next_line.c get_next_line_utils.c main_bonus.c

FILES_O = $(FILES:.c=.o)

BONUS_O = $(BONUS_FILES:.c=.o)

$(NAME) : $(FILES_O)
	$(CC) $(CFLAGS) $(FILES_O) -o $(NAME) 

all : $(NAME) $(BONUS_O)

bonus : $(BONUS_O)
	
$(BONUS_O): $(BONUS_FILES)
	cc $(CFLAGS) -c $(BONUS_FILES) 
	cc $(CFLAGS) $(BONUS_FILES) -o $(NAME_BONUS)

clean :
	rm -f $(FILES_O) $(BONUS_O)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean