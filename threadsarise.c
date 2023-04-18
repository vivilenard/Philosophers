/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsarise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:33:48 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/18 20:47:00 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

void msleep(int ms)
{
	// t_us	us;
	// int		i;
	
	// us = ms * 1000;
	// i = ms;
	// while (ms)
	// {
	// 	usleep(1000);
	// 	ms--;
	// }
	//usleep(ms * 1000);
	t_ms max;

	max = clock() + (t_ms)ms;
	while (clock() < max)
	{
		usleep(100);
	}
}

//10 * 1000 = 10000;

int	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printstate(philo, e_fork);
		pthread_mutex_lock(philo->left_fork);
		printstate(philo, e_fork);
	}
	else
	{
		usleep(1);
		pthread_mutex_lock(philo->left_fork);
		printstate(philo, e_fork);
		pthread_mutex_lock(philo->right_fork);
		printstate(philo, e_fork);
	}
	philo->last_meal = timestamp(philo);
	printstate(philo, e_eat);
	msleep(philo->info->t_eat);
	//usleep(philo->info->t_eat * 1000);
	philo->number_meals += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int sleeep(t_philo *philo)
{
	printstate(philo, e_sleep);
	msleep(philo->info->t_sleep);
	return (1);
}

int	think(t_philo *philo)
{
	printstate(philo, e_think);
	return (1);
}

void	*philo_arise(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		eat(philo);
		sleeep(philo);
		think(philo);
		//break ;
	}
	return (NULL);
}

int	cometothetable(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (pthread_create(&philos[i]->tid, NULL, philo_arise, philos[i]) != 0)
			return (0);
		usleep(1);
		i++;
	}
	return (1);
}