CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = philo
SRC = main.c initstructs.c utils.c threadsarise.c cleanandfreethetable.c
OBJ = $(SRC:.c=.o)
ARG = 4 800 200 200 

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o philo 
run: re
	./philo $(ARG)
run1: re
	./philo 1 800 200 200
run2: re
	./philo 5 800 200 200
run3: re
	./philo 5 800 200 200 7
run4: re
	./philo 4 410 200 200
run5: re
	./philo 4 310 200 100
run6: re
	./philo 4 200 200 900
run7: re
	./philo 2 405 200 200
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f ./$(NAME)
re: fclean all