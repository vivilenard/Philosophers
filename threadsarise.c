/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsarise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:33:48 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/23 16:01:22 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

void	*philo_arise(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (keep_going(philo))
	{
		if (!eat(philo))
			break ;
		if (!sleeep(philo))
			break ;
		if (!think(philo))
			break ;
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
