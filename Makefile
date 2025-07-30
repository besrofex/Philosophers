NAME = philo
FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
CC = cc 
SRC = philo.c utils.c parse.c init.c init_utils.c routine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: clean