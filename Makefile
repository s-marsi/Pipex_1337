CFLAGS = -Wall -Wextra -Werror

CC = cc

AR = ar -r

NAME = pipex

FILES = ft_split.c ft_strlcpy.c ft_strnstr.c ft_strjoin.c pipex.c get_path.c main.c

# BONUS_FILES = 

FILES_O = $(FILES:.c=.o)

# BONUS_O = $(BONUS_FILES:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(FILES_O)
	$(CC) $(CFLAGS) $(FILES_O) -o $(NAME) 

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