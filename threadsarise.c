/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsarise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:33:48 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/13 14:35:45 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

void	*philo_arise(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		//eat(philo, philo->shared, philo->params);
		eatt();
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
