/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initphilos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:00:35 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/17 08:46:23 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

t_info	*initinfo(char **argv, t_ms starttime)
{
	t_info *info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->n_philos = ft_atoi(argv[1]);
	info->starttime = starttime;
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	set_forks(info);
	pthread_mutex_init(&info->printlock, NULL);
	printf("n_philos: %d, t_die: %d, t_eat: %d, t_sleep: %d\n", info->n_philos, info->t_die, info->t_eat, info->t_sleep);
	return (info);
}

int	init_philo_data(t_philo **philo, t_info *info,  int i)
{
	philo[i]->id = i + 1;
	philo[i]->info = info;
	philo[i]->last_eaten = timestamp(philo[i]);
	philo[i]->fork = info->fork[i];
	if (!info->fork[i + 1])
		philo[i]->fork_right = info->fork[0];
	else
		philo[i]->fork_right = info->fork[i + 1];
	return (0);
}

void	set_forks(t_info *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t *) * info->n_philos);
	while (i < info->n_philos)
	{
		info->fork[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(info->fork[i], NULL);
		i++;
	}
	info->fork[i] = NULL;
}

// t_shared	*initshared(t_info *info)
// {
// 	t_shared	*shared;

// 	shared = malloc(sizeof(t_shared));
	// pthread_mutex_init(&shared->printlock, NULL);
	// pthread_mutex_init(&shared->timelock, NULL);
	// pthread_mutex_init(&shared->lock, NULL);
// 	set_forks(shared, info);
// 	return (shared);
// }

t_philo	**initphilos(char **argv, t_ms starttime)
{
	t_philo		**philos;
	t_info		*info;
	int			i;

	info = initinfo(argv, starttime);
	//shared = initshared(info);
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
	// printf("n->philos %d, philoscreated %d, starttime %ld\n", info->n_philos, i, info->starttime);
	// i = 0;
	// while (philos[i])
	// {
	// 	printf("philo %d\n", philos[i]->id);
	// 	i++;
	// }
	return (philos);
}