# ifndef EXISTENTIALISM_H
# define EXISTENTIALISM_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

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
	struct s_params	*params;
	struct s_shared	*shared;
	int				id;
	//struct s_philo *rightside;
	pthread_mutex_t *fork;
	pthread_mutex_t *fork_right;
	int				last_eaten;
	pthread_t		tid;
}		t_philo;

typedef struct s_params
{
	int		n_philos;
	t_us	starttime;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
}		t_params;

typedef struct s_shared
{
	pthread_mutex_t	printlock;
	pthread_mutex_t	**fork;
}		t_shared;

//initphilos
t_philo		**initphilos(char **argv, t_us starttime);
t_params	*initparams(char **argv, t_us starttime);
int			init_philo_data(t_philo **philo, t_params *params, t_shared *shared, int i);

//utils
int			ft_atoi(char *str);
void		printstate(t_philo *philo, int x);

//threadsarise
void		*philo_arise(void *ptr);
int			cometothetable(t_philo **philos);

//cleanandfree
int			cleanthetable(t_philo *philos);
#endif