/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:01:12 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/21 18:27:55 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	takeforks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (printstate(timestamp(philo), philo, e_die), 0);
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
	return (1);
}

void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->count_meals);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->count_meals);
}

int	eat(t_philo *philo)
{
	if (!takeforks(philo))
		return (0);
	pthread_mutex_lock(&philo->timeofmeal);
	philo->last_meal = timestamp(philo);
	pthread_mutex_unlock(&philo->timeofmeal);
	printstate(philo->last_meal, philo, e_eat);
	msleep(philo->info->t_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	sleeep(t_philo *philo)
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
