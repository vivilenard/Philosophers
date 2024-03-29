/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:01:12 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/24 12:55:27 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	takeforks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printstate(timestamp(philo), philo, e_fork);
		if (philo->info->n_philos == 1)
		{
			msleep(philo->info->t_die);
			pthread_mutex_unlock(philo->right_fork);
			return (printstate(timestamp(philo), philo, e_die), 0);
		}
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

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	eat(t_philo *philo)
{
	if (!takeforks(philo))
		return (0);
	pthread_mutex_lock(&philo->timeofmeal);
	philo->last_meal = timestamp(philo);
	pthread_mutex_unlock(&philo->timeofmeal);
	if (!printstate(philo->last_meal, philo, e_eat))
		return (unlock_forks(philo), 0);
	msleep(philo->info->t_eat);
	count_meals(philo);
	unlock_forks(philo);
	return (1);
}

int	sleeep(t_philo *philo)
{
	int	sleeptime;

	sleeptime = philo->info->t_sleep;
	if (sleeptime > 2000)
	{
		if (sleeptime + philo->info->t_eat > philo->info->t_die)
			return (0);
	}
	if (!printstate(timestamp(philo), philo, e_sleep))
		return (0);
	msleep(sleeptime);
	return (1);
}

int	think(t_philo *philo)
{
	if (!printstate(timestamp(philo), philo, e_think))
		return (0);
	return (1);
}
