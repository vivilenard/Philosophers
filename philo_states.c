/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:01:12 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/19 12:21:20 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

void	takeforks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printstate(timestamp(philo), philo, e_fork);
		pthread_mutex_lock(philo->left_fork);
		printstate(timestamp(philo), philo, e_fork);
	}
	else
	{
		usleep(1);
		pthread_mutex_lock(philo->left_fork);
		printstate(timestamp(philo), philo, e_fork);
		pthread_mutex_lock(philo->right_fork);
		printstate(timestamp(philo), philo, e_fork);
	}
}

int	eat(t_philo *philo)
{
	takeforks(philo);
	philo->last_meal = timestamp(philo);
	printstate(timestamp(philo), philo, e_eat);
	msleep(philo->info->t_eat);
	pthread_mutex_lock(&philo->count_meals);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->count_meals);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int sleeep(t_philo *philo)
{
	printstate(timestamp(philo), philo, e_sleep);
	msleep(philo->info->t_sleep);
	return (1);
}

int	think(t_philo *philo)
{
	printstate(timestamp(philo), philo, e_think);
	return (1);
}
