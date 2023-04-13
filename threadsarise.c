/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsarise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:33:48 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/10 19:35:26 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	takefork(t_philo *philo, t_shared *shared, int pos)
{
	int locked;

	locked = 99;
	if (pos == e_rightfork)
	{
		locked = pthread_mutex_lock(&shared->forks[philo->rightside->id]);
		if (locked == 0)
			philo->rightside->fork_taken = 1;
	}
	else
	{
		pthread_mutex_lock(&shared->forks[philo->id]);
		if (locked == 0)
			philo->fork_taken = 1;
	}
	if (locked == 0)
		return (printstate(philo, e_fork, 0), 1);
	printf("haallo %d\n", locked);
	return (0);
}

void	putdownfork(t_philo *philo, int whichfork)
{
	int	unlocked;
	
	if (whichfork == 0)
	{
		unlocked = pthread_mutex_unlock(&philo->shared->forks[philo->id]);
		printstate(philo, e_downfork, -1);
		return ;
	}
	else if (whichfork == 1)
	{
		unlocked = pthread_mutex_unlock(&philo->shared->forks[philo->rightside->id]);
		printstate(philo, e_downrightfork, -1);
		return ;
	}	
}

int	eat(t_philo *philo, t_shared *shared, t_params *params)
{
	pthread_mutex_lock(&shared->universal);
	if (philo->rightside->fork_taken == 1)
		return (0);
	if (!takefork(philo, shared, 0))
		return (0);
	printf("hi\n");
	if (!takefork(philo, shared, 1))
		return (0);
	pthread_mutex_unlock(&shared->universal);
	printstate(philo, e_eat, -1);
	usleep(params->t_eat);
	putdownfork(philo, e_fork);
	putdownfork(philo, e_rightfork);
	return (1);
}

int sleeep(t_philo *philo)
{
	printstate(philo, e_sleep, -1);
	usleep(philo->params->t_sleep);
	return (1);
}

int	think(t_philo *philo)
{
	printstate(philo, e_think, -1);
	return (1);
}

void	*philo_arise(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (!eat(philo, philo->shared, philo->params))
			continue ;
		sleeep(philo);
		think(philo);
		break;
	}
	// pthread_mutex_lock(&philo->params->lock);
	// printf("i am philo %d\n", philo->id);
	// pthread_mutex_unlock(&philo->params->lock);
	return (NULL);
}

int	cometothetable(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->n_philos)
	{
		if (pthread_create(&philos[i].tid, NULL, philo_arise, &philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}