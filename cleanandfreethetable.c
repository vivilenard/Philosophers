/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanandfreethetable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:36:52 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/17 08:46:38 by vlenard          ###   ########.fr       */
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
		//printf("joined %d\n", philos[i]->id);
		i++;
	}
	return (1);
}
