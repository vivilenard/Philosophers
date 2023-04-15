CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = philo
SRC = main.c initphilos.c utils.c threadsarise.c cleanandfreethetable.c time.c
OBJ = $(SRC:.c=.o)
ARG = 5 800 200 200 

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o philo 
run: re
	./philo $(ARG)
run1: all
	./philo 1 800 200 200
run2: all
	./philo 5 800 200 200
run3: all
	./philo 5 800 200 200 7
run4: all
	./philo 4 410 200 200
run5: all
	./philo 4 310 200 100
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f ./$(NAME)
re: fclean all