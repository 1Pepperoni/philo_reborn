CFLAGS=-Werror -Wextra -Wall #-g -fsanitize=thread
NAME= philo

SRC= philo.c\
	utils.c\
	parsing.c

OBJ= ${SRC:%.c=%.o}

$(NAME): ${OBJ}
	gcc $(OBJ) -o $(NAME) $(CFLAGS)

all:	${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
