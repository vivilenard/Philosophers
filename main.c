/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/19 12:23:42 by vlenard          ###   ########.fr       */
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

int	everything_alright(t_philo **philos, t_info *info)
{
	int	i;
	int	full_stomach;

	i = 0;
	full_stomach = 1;
	if (info->n_meals == 0)
		return (0);
	while (philos[i])
	{
		usleep(3000);
		if (starved(philos[i]))
		{
			//printf("%s, clock: %lu, last meal: %lu\n", YELLOW, timestamp(philos[i]), philos[i]->last_meal);
			printstate(timestamp(philos[i]), philos[i], e_die);
			return (0);
		}
		pthread_mutex_lock(&philos[i]->count_meals);
		if (info->n_meals > -1 && philos[i]->meals_eaten < info->n_meals)
			full_stomach = -1;
		pthread_mutex_unlock(&philos[i]->count_meals);
		i++;
	}
	if (full_stomach == 1)
	{
		printf("full\n");
		i = 0;
		while (philos[i])
		{
			printf("%d, meals %d\n", philos[i]->id, philos[i]->meals_eaten);
			i++;
		}
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		**philos;

	if (argc < 5 || argc > 6)
		return (0);
	philos = initphilos(argv, clock());
	printf("%d\n", (*philos)->info->n_meals);
	if (!philos)
		return (0);
	if (!cometothetable(philos))
		return (0);
	while	(everything_alright(philos, (*philos)->info) == 1)
		;
	cleanthetable(philos, (*philos)->info);
	return (0);
}
	// int	i;
	// // int	full_stomach;

	// // full_stomach = 1;
	// i = 0;
	// while (philos[i])
	// {
	// 	if (timestamp(philos[i]) - philos[i]->last_meal > (unsigned long)info->t_die)
	// 	{
	// 		//printf("clock: %lu, last meal: %lu\n", timestamp(philos[i]), philos[i]->last_meal);
	// 		printstate(philos[i], e_die);
	// 		return (0);
	// 	}
	// 	// if (philos[i]->number_meals < info->n_meals)
	// 	// 	full_stomach = 2;
	// 	usleep(3000);
	// 	i++;
	// }
	// // if (full_stomach == 2)
	// // 	return (-1);
	// return (1);