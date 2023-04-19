/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanandfreethetable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:36:52 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/19 17:57:47 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	cleanthetable(t_philo **philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
	{
		pthread_detach(philos[i]->tid);
		pthread_mutex_destroy(info->fork[i]);
		pthread_mutex_destroy(&philos[i]->count_meals);
		free(philos[i]);
		i++;
	}
	pthread_mutex_unlock(&info->printlock);
	pthread_mutex_destroy(&info->printlock);
	free(info->fork);
	free(info);
	free(philos);
	return (1);
}
