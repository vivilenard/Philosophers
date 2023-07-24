/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:49:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/13 14:34:43 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

// int	takefork(t_philo *philo, t_shared *shared, int pos)
// {
// 	int locked;

// 	locked = 99;
// 	if (pos == e_rightfork)
// 	{
// 		locked = pthread_mutex_lock(&shared->forks[philo->rightside->id]);
// 		if (locked == 0)
// 			philo->rightside->fork_taken = 1;
// 	}
// 	else
// 	{
// 		locked = pthread_mutex_lock(&shared->forks[philo->id]);
// 		if (locked == 0)
// 			philo->fork_taken = 1;
// 	}
// 	if (locked == 0)
// 		return (printstate(philo, e_fork, 0), 1);
// 	printf("haallo %d\n", locked);
// 	return (0);
// }

// void	putdownfork(t_philo *philo, int whichfork)
// {
// 	int	unlocked;
	
// 	if (whichfork == 0)
// 	{
// 		unlocked = pthread_mutex_unlock(&philo->shared->forks[philo->id]);
// 		printstate(philo, e_downfork, -1);
// 		return ;
// 	}
// 	else if (whichfork == 1)
// 	{
// 		unlocked = pthread_mutex_unlock(&philo->shared->forks[philo->rightside->id]);
// 		printstate(philo, e_downrightfork, -1);
// 		return ;
// 	}	
// }

// int	eat(t_philo *philo, t_shared *shared, t_params *params)
// {
// 	printf("hi\n");
// 	pthread_mutex_lock(&shared->universal);
// 	if (philo->rightside->fork_taken == 1)
// 		return (0);
// 	if (!takefork(philo, shared, 0))
// 		return (0);
// 	if (!takefork(philo, shared, 1))
// 		return (0);
// 	pthread_mutex_unlock(&shared->universal);
// 	printstate(philo, e_eat, -1);
// 	usleep(params->t_eat);
// 	putdownfork(philo, e_fork);
// 	putdownfork(philo, e_rightfork);
// 	return (1);
// }

// int	takefork(pthread_mutex_t fork, t_shared *shared)
// {
// 	pthread_mutex_lock(&fork);
// 	return (0);
// }

// int	eat(t_philo *philo, t_shared *shared, t_params *params)
// {
// 	//printf("%d\n", philo->id - 1);
// 	pthread_mutex_lock(&shared->forks[philo->id - 1]);
// 	//printstate(philo, e_eat);
// 	usleep(params->t_eat);
// 	pthread_mutex_unlock(&shared->forks[philo->id - 1]);
// 	return (1);
// }

int	eatt()
{
	return (1);
}

int sleeep(t_philo *philo)
{
	printstate(philo, e_sleep);
	usleep(philo->params->t_sleep);
	return (1);
}

int	think(t_philo *philo)
{
	printstate(philo, e_think);
	return (1);
}
