/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:56:31 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/23 18:03:48 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	starved(t_philo *philo)
{
	t_ms	time_die;

	time_die = (t_ms)philo->info->t_die;
	pthread_mutex_lock(&philo->timeofmeal);
	if (timestamp(philo) - philo->last_meal > time_die)
		return (pthread_mutex_unlock(&philo->timeofmeal), 1);
	pthread_mutex_unlock(&philo->timeofmeal);
	return (0);
}

int	check_everybody_satisfied(t_info *info)
{
	pthread_mutex_lock(&info->check_end);
	if (info->full_stomach == 1)
	{
		info->finished = 1;
		return (pthread_mutex_unlock(&info->check_end), 0);
	}
	pthread_mutex_unlock(&info->check_end);
	return (1);
}

int	everybody_alive(t_philo **philos, t_info *info)
{
	int	i;

	i = 0;
	if (info->n_meals > -1)
		info->full_stomach = 1;
	while (philos[i])
	{
		if (starved(philos[i]))
			return (printstate(timestamp(philos[i]), philos[i], e_die), 0);
		pthread_mutex_lock(&philos[i]->count_meals);
		if (info->n_meals > -1 && philos[i]->meals_eaten < info->n_meals)
			info->full_stomach = -1;
		pthread_mutex_unlock(&philos[i]->count_meals);
		i++;
	}
	return (1);
}
