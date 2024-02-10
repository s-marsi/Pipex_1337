#CFLAGS = -Wall -Wextra -Werror

AR = ar -r

NAME = pipex.a

FILES = ft_split.c ft_strlcpy.c ft_strnstr.c ft_strjoin.c pipex.c main.c

# BONUS_FILES = 

FILES_O = $(FILES:.c=.o)

# BONUS_O = $(BONUS_FILES:.c=.o)

all : $(NAME)

$(NAME) : $(FILES_O)
	$(AR) $(NAME) $(FILES_O)

# bonus : $(BONUS_O)

# $(BONUS_O): $(BONUS_FILES)
# 	cc $(CFLAGS) -c $(BONUS_FILES) 
# 	$(AR) $(NAME) $(BONUS_O)

clean :
	rm -f $(FILES_O) 
# $(BONUS_O)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean