/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:10:15 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/21 18:25:44 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_info
{
	int				n_philos;
	t_ms			starttime;
	int				t_die;
	int				t_eat;
	int				t_sleep;
//	int				n_eat;
	int				n_meals;
	int				full_stomach;
	int				finished;
	pthread_mutex_t	**fork;
	pthread_mutex_t	printlock;
	pthread_mutex_t	check_end;
}		t_info;

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	t_ms			last_meal;
	int				meals_eaten;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	count_meals;
	pthread_mutex_t	timeofmeal;
	pthread_t		tid;
}		t_philo;

//initphilos
t_philo		**initphilos(char **argv, t_ms starttime);
t_info		*initinfo(char **argv, t_ms starttime);
int			init_philo_data(t_philo **philo, t_info *info, int i);
void		set_forks(t_info *info);

//threadsarise
void		*philo_arise(void *ptr);
int			cometothetable(t_philo **philos);
int			keep_going(t_philo *philo);

//states
int			eat(t_philo *philo);
int			takeforks(t_philo *philo);
int 		sleeep(t_philo *philo);
int			think(t_philo *philo);

//cleanandfree
void		cleanthetable(t_philo **philos, t_info *info);
void		free_stuff(t_philo **philos, t_info *info);

//checker
int			everybody_alive(t_philo **philos, t_info *info);
int			check_everybody_satisfied(t_info *info);
int			starved(t_philo *philo);

//utils
int			ft_atoi(char *str);
int			printstate(t_ms time, t_philo *philo, int x);
t_ms		current_time();
t_ms		timestamp(t_philo *philo);
void		msleep(int ms);

#endif