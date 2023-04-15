/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/15 17:24:08 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	are_we_alive(t_philo **philos, t_params *params)
{
	int	i;

	while (1)
	{
		i = 0;
		while (philos[i])
		{
			if (clock() - philos[i]->last_eaten > (unsigned long)params->t_die)
			{
				printf("clock: %lu, last meal: %lu\n", clock(), philos[i]->last_eaten);
				printf("time since last eaten %lu\n", clock() - philos[i]->last_eaten);
				philos[i]->alive = 0;
				printstate(philos[i], e_die);
				return (0);
			}
			i++;
		}
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
	if (!are_we_alive(philos, (*philos)->params))
		return (0);
	cleanthetable(philos, (*philos)->params);
	return (0);
}

	//pthread_t	master;
	//pthread_create(&master, NULL, check_if_alive, philos);
// void	*check_if_alive(void *p)
// {
// 	t_philo **philos;
// 	int		i;

// 	philos = (t_philo **)p;
// 	while (1)
// 	{
// 		i = 0;
// 		while (philos[i])
// 		{
// 			if (clock() - philos[i]->last_eaten > 80)
// 			{
// 				printf("clock: %lu, last meal: %lu\n", clock(), philos[i]->last_eaten);
// 				printf("time since last eaten %lu\n", clock() - philos[i]->last_eaten);
// 				philos[i]->alive = 0;
// 				printstate(philos[i], e_die);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 	}
// 	return (NULL);
// }