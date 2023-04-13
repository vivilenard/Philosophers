/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initphilos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:00:35 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/10 18:45:29 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

t_params	*initparams(char **argv)
{
	t_params *params;

	params = malloc(sizeof(t_params));
	if (!params)
		return (NULL);
	params->n_philos = ft_atoi(argv[1]);
	params->t_die = ft_atoi(argv[2]);
	params->t_eat = ft_atoi(argv[3]);
	params->t_sleep = ft_atoi(argv[4]);
	return (params);
}

int	init_philo_data(t_philo *philo, t_params *params, t_shared *shared, int i)
{
	philo->id = i + 1;
	philo->fork_taken = 0;
	philo->params = params;
	philo->shared = shared;
	philo->last_eaten = 0;
	philo->rightside = philo + 1;
	philo->leftside = philo - 1;
	return (0);
}

int	set_forks(t_shared *shared, t_params *params)
{
	int i;

	shared->forks = malloc(sizeof(pthread_mutex_t) * params->n_philos);
	if (!shared->forks)
		return (0);
	i = 0;
	while (i < params->n_philos)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) == -1)
			return (perror("pthreadinit failed"), -1);
		i++;
	}
	printf("forks created %d\n", i);
	return (1);
}

t_shared	*initshared(t_params *params)
{
	t_shared	*shared;

	shared = malloc(sizeof(t_shared));
	if (!shared)
		return (NULL);
	pthread_mutex_init(&shared->printlock, NULL);
	pthread_mutex_init(&shared->universal, NULL);
	set_forks(shared, params);
	return (shared);
}

t_philo	*initphilos(t_params *params, t_shared *shared, t_us starttime)
{
	t_philo *philos;
	int	i;

	philos = malloc(params->n_philos * sizeof(t_philo));
	if (!philos || !params || !shared)
		return (0);
	i = 0;
	while (i < params->n_philos)
	{
		init_philo_data(&philos[i], params, shared, i);
		philos[i].params->starttime = starttime;
		i++;
	}
	philos[params->n_philos - 1].rightside = &philos[0];
	philos[0].leftside = &philos[params->n_philos - 1];
	printf("hi\n");
	i = 0;
	while (i < params->n_philos)
	{
		printf("id %d id_right %d id_left %d\n", philos[i].id, philos[i].rightside->id, philos[i].leftside->id); 
		i++;
	}
	printf("n->philos %d, philoscreated %d, starttime %ld\n", params->n_philos, i, params->starttime);
	return (philos);
}

t_philo	*initstructs(char **argv, t_us starttime)
{
	t_philo		*philos;
	t_params	*params;
	t_shared	*shared;

	params = initparams(argv);
	shared = initshared(params);
	philos = initphilos(params, shared, starttime);
	return (philos);
}