/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initphilos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:00:35 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/15 13:57:37 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

t_params	*initparams(char **argv, t_us starttime)
{
	t_params *params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->n_philos = ft_atoi(argv[1]);
	params->starttime = starttime;
	params->t_die = ft_atoi(argv[2]);
	params->t_eat = ft_atoi(argv[3]);
	params->t_sleep = ft_atoi(argv[4]);
	return (params);
}

int	init_philo_data(t_philo **philo, t_params *params, t_shared *shared, int i)
{
	philo[i]->id = i + 1;
	philo[i]->params = params;
	philo[i]->shared = shared;
	philo[i]->last_eaten = 0;
	philo[i]->fork = shared->fork[i];
	if (!shared->fork[i + 1])
		philo[i]->fork_right = shared->fork[0];
	else
		philo[i]->fork_right = shared->fork[i + 1];
	return (0);
}

void	set_forks(t_shared *shared, t_params *params)
{
	int	i;

	i = 0;
	shared->fork = malloc(sizeof(pthread_mutex_t *) * params->n_philos);
	while (i < params->n_philos)
	{
		shared->fork[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(shared->fork[i], NULL);
		i++;
	}
	shared->fork[i] = NULL;
}

t_shared	*initshared(t_params *params)
{
	t_shared	*shared;

	shared = malloc(sizeof(t_shared));
	pthread_mutex_init(&shared->printlock, NULL);
	set_forks(shared, params);
	return (shared);
}

t_philo	**initphilos(char **argv, t_us starttime)
{
	t_philo		**philos;
	t_params	*params;
	t_shared	*shared;
	int			i;

	params = initparams(argv, starttime);
	shared = initshared(params);
	philos = malloc (sizeof(t_philo *) * params->n_philos);
	philos[params->n_philos] = NULL;
	if (!philos || !params)
		return (0);
	i = 0;
	while (i < params->n_philos)
	{
		philos[i] = malloc (sizeof(t_philo));
		init_philo_data(philos, params, shared, i);
		i++;
	}
	printf("n->philos %d, philoscreated %d, starttime %ld\n", params->n_philos, i, params->starttime);
	return (philos);
}