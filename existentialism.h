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
	e_leftfork = -1,
	e_fork = 0,
	e_rightfork = 1,
	e_eat = 2,
	e_sleep = 3,
	e_think = 4,
	e_die = 5,
	e_downfork = 6,
	e_downrightfork = 7
};

typedef struct s_philo
{
	struct s_params	*params;
	struct s_shared	*shared;
	int				id;
	int				fork_taken;
	int				last_eaten;
	pthread_t		tid;
	// pthread_mutex_t	fork;
	// pthread_mutex_t rightfork;
	// pthread_mutex_t leftfork;
	struct s_philo *rightside;
	struct s_philo *leftside;
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
	pthread_mutex_t universal;
	pthread_mutex_t	*forks;
}		t_shared;

//initphilos
t_philo		*initphilos(t_params *params, t_shared *shared, t_us starttime);
t_philo		*initstructs(char **argv, t_us starttime);
t_params	*initparams(char **argv);
int			init_philo_data(t_philo *philo, t_params *params, t_shared *shared, int i);

//utils
int			ft_atoi(char *str);
void		printstate(t_philo *philo, int x);

//threadsarise
void		*philo_arise(void *ptr);
int			cometothetable(t_philo *philos);

//philos
int		eat(t_philo *philo, t_shared *shared, t_params *params);
int		eatt(void);
int		sleeep(t_philo *philo);
int		think(t_philo *philo);
//void	putdownfork(t_philo *philo, int whichfork);
//int		takefork(t_philo *philo, t_shared *shared, int pos);
int	takefork(pthread_mutex_t fork, t_shared *shared);

//cleanandfree
int			cleanthetable(t_philo *philos);
#endif