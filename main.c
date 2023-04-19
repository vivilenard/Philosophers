/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/19 11:39:43 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	starved(t_philo *philo)
{
	t_ms	time_die;

	time_die = (t_ms)philo->info->t_die;
	if (timestamp(philo) - philo->last_meal > time_die)
		return (1);
	return (0);
}

int	everything_alright(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (starved(philos[i]))
		{
			//printf("%s, clock: %lu, last meal: %lu\n", YELLOW, timestamp(philos[i]), philos[i]->last_meal);
			printstate(timestamp(philos[i]), philos[i], e_die);
			return (0);
		}
		
		usleep(3000);
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
	while	(everything_alright(philos))
		;
	cleanthetable(philos, (*philos)->info);
	return (0);
}
