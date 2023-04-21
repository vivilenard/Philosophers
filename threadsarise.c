/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsarise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:33:48 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/21 18:13:19 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	keep_going(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->check_end);
	if (philo->info->finished)
		return (pthread_mutex_unlock(&philo->info->check_end), 0);
	pthread_mutex_unlock(&philo->info->check_end);
	return (1);
}

void	*philo_arise(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (keep_going(philo))
	{
		eat(philo);
		sleeep(philo);
		think(philo);
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
		usleep(10);
		i++;
	}
	return (1);
}
