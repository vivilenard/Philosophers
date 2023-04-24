/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:59:01 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/24 13:36:21 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

int	ft_atoi(char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

long int	ft_atol(char *str)
{
	long int	i;
	long int	s;
	long int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

void	if_die_finish(t_philo *philo, int x)
{
	if (x == e_die)
	{
		pthread_mutex_lock(&philo->info->check_end);
		philo->info->finished = 1;
		pthread_mutex_unlock(&philo->info->check_end);
	}
}

int	printstate(t_ms time, t_philo *philo, int x)
{
	const char	*state[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};
	const char	*color[] = {
		CYAN,
		RED,
		PURPLE,
		BLUE,
		YELLOW
	};

	if (!philo || x < 0 || x > 4)
		return (0);
	pthread_mutex_lock(&philo->info->printlock);
	if (!keep_going(philo))
		return (pthread_mutex_unlock(&philo->info->printlock), 0);
	if_die_finish(philo, x);
	printf("%s %ld %d %s\n", color[x], time, philo->id, state[x]);
	pthread_mutex_unlock(&philo->info->printlock);
	return (1);
}

void	count_meals(t_philo *philo)
{
	if (philo->info->n_meals)
	{
		pthread_mutex_lock(&philo->count_meals);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->count_meals);
	}
}
