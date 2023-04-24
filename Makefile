CC = cc
CFLAGS = -Wall -Werror -Wextra  #-fsanitize=thread -g 
NAME = philo
SRC = main.c time.c checker.c initstructs.c utils.c threadsarise.c philo_states.c freethetable.c
OBJ = $(SRC:.c=.o)
ARG = 4 800 200 200 

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o philo -lpthread #-fsanitize=thread #-lpthread
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
	./philo 20 109 50 60
run8: re
	./philo 3 20 10 10
run9: re
	./philo 5 200 50 50 2
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f ./$(NAME)
re: fclean all

#lpthread

LSANLIB = /LeakSanitizer/liblsan.a
lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK += -LLeakSanitizer -llsan -lc++
lsan: fclean $(LSANLIB)
lsan: all
$(LSANLIB):
	@if [ ! -d "LeakSanitizer" ]; then git clone https://github.com/mhahnFr/LeakSanitizer.git; fi
	@$(MAKE) -C LeakSanitizer

$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git

$(LSANLIB): $(LSAN)
	$(MAKE) -C LeakSanitizer3
	