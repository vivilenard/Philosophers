/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:00:35 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/24 13:33:38 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

t_info	*initinfo(char **argv, t_ms starttime)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->n_philos = ft_atoi(argv[1]);
	info->starttime = starttime;
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_meals = -1;
	info->full_stomach = -1;
	if (argv[5])
		info->n_meals = ft_atoi(argv[5]);
	info->finished = 0;
	set_forks(info);
	pthread_mutex_init(&info->printlock, NULL);
	pthread_mutex_init(&info->check_end, NULL);
	return (info);
}

int	init_philo_data(t_philo **philo, t_info *info, int i)
{
	philo[i]->info = info;
	philo[i]->id = i + 1;
	philo[i]->last_meal = timestamp(philo[i]);
	philo[i]->left_fork = info->fork[i];
	philo[i]->meals_eaten = 0;
	if (!info->fork[i + 1])
		philo[i]->right_fork = info->fork[0];
	else
		philo[i]->right_fork = info->fork[i + 1];
	pthread_mutex_init(&philo[i]->count_meals, NULL);
	pthread_mutex_init(&philo[i]->timeofmeal, NULL);
	return (0);
}

void	set_forks(t_info *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t *) * (info->n_philos + 1));
	while (i < info->n_philos)
	{
		info->fork[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(info->fork[i], NULL);
		i++;
	}
	info->fork[i] = NULL;
}

t_philo	**initphilos(char **argv, t_ms starttime)
{
	t_philo		**philos;
	t_info		*info;
	int			i;

	if (ft_atoi(argv[1]) > 500)
		return (printf("There are only 500 chairs. Try again\n"), NULL);
	info = initinfo(argv, starttime);
	philos = malloc (sizeof(t_philo *) * (info->n_philos + 1));
	if (!philos || !info)
		return (0);
	i = 0;
	while (i < info->n_philos)
	{
		philos[i] = malloc (sizeof(t_philo));
		init_philo_data(philos, info, i);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
