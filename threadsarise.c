/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsarise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:33:48 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/13 15:56:08 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	eat(t_philo *philo)
{
	printstate(philo, e_eat);
	return (1);
}

int sleeep(t_philo *philo)
{
	usleep(philo->params->t_sleep);
	printstate(philo, e_sleep);
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
		break;
	}
	return (NULL);
}

int	cometothetable(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (pthread_create(&philos[i]->tid, NULL, philo_arise, *(philos + i)) != 0)
			return (0);
		i++;
	}
	return (1);
}