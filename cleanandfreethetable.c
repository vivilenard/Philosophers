/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanandfreethetable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:36:52 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/21 16:58:20 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	cleanthetable(t_philo **philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
	{
		pthread_join(philos[i]->tid, NULL);
		i++;
	}
	i = 0;
	while (i < info->n_philos)
	{
		//pthread_mutex_unlock(info->fork[i]);
		pthread_mutex_destroy(info->fork[i]);
		free(info->fork[i]);
		pthread_mutex_destroy(&philos[i]->count_meals);
		free(philos[i]);
		i++;
	}
	//pthread_mutex_unlock(&info->printlock);
	pthread_mutex_destroy(&info->printlock);
	pthread_mutex_destroy(&info->check_end);
	free(info->fork);
	free(info);
	free(philos);
	return (1);
}
