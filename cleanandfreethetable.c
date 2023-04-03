/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanandfreethetable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:36:52 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/03 18:37:05 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	cleanthetable(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->n_philos)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
	return (1);
}
