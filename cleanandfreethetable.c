/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanandfreethetable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:36:52 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/15 16:57:40 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	cleanthetable(t_philo **philos, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->n_philos)
	{
		pthread_join(philos[i]->tid, NULL);
		//printf("joined %d\n", philos[i]->id);
		i++;
	}
	return (1);
}
