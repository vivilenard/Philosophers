CC = cc
CFLAGS = -Wall -Werror -Wextra 
NAME = philo
SRC = main.c time.c checker.c initstructs.c utils.c threadsarise.c philo_states.c freethetable.c
OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o philo
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f ./$(NAME)
re: fclean all
