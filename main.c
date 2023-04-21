/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/21 18:17:23 by vlenard          ###   ########.fr       */
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
	if (info->full_stomach == 1)
	{
		pthread_mutex_lock(&info->check_end);
		info->finished = 1;
		pthread_mutex_unlock(&info->check_end);
		return (1);
	}
	return (0);
}

int	everybody_alive(t_philo **philos, t_info *info)
{
	int	i;

	i = 0;
	info->full_stomach = 1;
	while (philos[i])
	{
		usleep(3000);
		if (starved(philos[i]))
		{
			printstate(timestamp(philos[i]), philos[i], e_die);
			pthread_mutex_lock(&info->check_end);
			info->finished = 1;
			pthread_mutex_unlock(&info->check_end);
			return (0);
		}
		pthread_mutex_lock(&philos[i]->count_meals);
		if (info->n_meals > -1 && philos[i]->meals_eaten < info->n_meals)
			info->full_stomach = -1;
		pthread_mutex_unlock(&philos[i]->count_meals);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		**philos;

	if (argc < 5 || argc > 6)
		return (0);
	//need more secure parsing
	philos = initphilos(argv, current_time());
	if (!philos)
		return (0);
	if (!cometothetable(philos))
		return (0);
	while (everybody_alive(philos, (*philos)->info))
		check_everybody_satisfied((*philos)->info);
	cleanthetable(philos, (*philos)->info);
	return (0);
}
