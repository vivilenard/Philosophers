/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/17 09:42:40 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	we_are_alive(t_philo **philos, t_info *info)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (timestamp(philos[i]) - philos[i]->last_eaten > (unsigned long)info->t_die)
		{
			printf("clock: %lu, last meal: %lu\n", timestamp(philos[i]), philos[i]->last_eaten);
			//printf("time since last eaten %lu\n", timestamp(philos[i]) - philos[i]->last_eaten);
			printstate(philos[i], e_die);
			//return (0);
		}
		usleep(10000);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		**philos;

	if (argc < 5 || argc > 6)
		return (0);
	philos = initphilos(argv, clock());
	if (!philos)
		return (0);
	if (!cometothetable(philos))
		return (0);
	while	(we_are_alive(philos, (*philos)->info))
		;
	//cleanthetable(philos, (*philos)->info);
	return (0);
}
