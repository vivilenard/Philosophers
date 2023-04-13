/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/10 19:05:30 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"


int	main(int argc, char **argv)
{
	t_philo *philos;
	if (argc < 5 || argc > 6)
		return (0);
	philos = initstructs(argv, clock());
	if (!philos)
		return (0);
	printf("t_eat %d\n", philos->params->t_eat);
	if (!cometothetable(philos))
		return (0);
	usleep(3000);
	cleanthetable(philos);
	return (0);
}