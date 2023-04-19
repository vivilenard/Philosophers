# ifndef EXISTENTIALISM_H
# define EXISTENTIALISM_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef unsigned long t_ms;
typedef unsigned long t_us;

enum philostate
{
	e_fork = 0,
	e_eat = 1,
	e_sleep = 2,
	e_think = 3,
	e_die = 4,
};

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	count_meals;
	t_ms			last_meal;
	int				meals_eaten;
	pthread_t		tid;
}		t_philo;

typedef struct s_info
{
	int				n_philos;
	t_ms			starttime;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				n_meals;
	pthread_mutex_t	**fork;
	pthread_mutex_t	printlock;
}		t_info;

//initphilos
t_philo		**initphilos(char **argv, t_ms starttime);
t_info		*initinfo(char **argv, t_ms starttime);
int			init_philo_data(t_philo **philo, t_info *info, int i);
void		set_forks(t_info *info);

//threadsarise
void		*philo_arise(void *ptr);
int			cometothetable(t_philo **philos);

//states
int			eat(t_philo *philo);
void		takeforks(t_philo *philo);
int 		sleeep(t_philo *philo);
int			think(t_philo *philo);

//cleanandfree
int			cleanthetable(t_philo **philos, t_info *info);

//checker
//int			we_are_alive(t_philo **philos, t_info *info);

//utils
int			ft_atoi(char *str);
void		printstate(t_ms time, t_philo *philo, int x);
t_ms		clock();
t_ms		timestamp(t_philo *philo);
void		msleep(int ms);

#endif