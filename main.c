/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/23 16:13:22 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

void	errormsg(void)
{
	printf("\nPlease enter four parameters:\n");
	printf("'Number of philos' , 'time to die', ");
	printf("'time to eat' and 'time to sleep'\n");
	printf("\t+ optional: 'Number of times each philo must eat'\n");
	printf("time is interpreted in [ms]\n");
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	n;

	if (argc < 5 || argc > 6)
		return (errormsg(), 0);
	i = 1;
	while (argv[i])
	{
		n = 0;
		while (argv[i][n])
		{
			if (argv[i][n] < '0' || argv[i][n] > '9')
				return (errormsg(), 0);
			if (ft_atoi(argv[i]) < 0)
			{
				printf("\nOnly positive integers allowed\n");
				return (errormsg(), 0);
			}
			n++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		**philos;

	if (!check_input(argc, argv))
		return (0);
	philos = initphilos(argv, current_time());
	if (!philos)
		return (0);
	if (!cometothetable(philos))
		return (0);
	while (everybody_alive(philos, (*philos)->info))
	{
		if (!check_everybody_satisfied((*philos)->info))
			break ;
		//usleep (100);
	}
	cleanthetable(philos, (*philos)->info);
	return (0);
}
