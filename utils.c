/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:59:01 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/19 11:33:57 by vlenard          ###   ########.fr       */
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

void	printstate(t_ms time, t_philo *philo, int x)
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

	if (x < 0 || x > 4)
		return ;
	pthread_mutex_lock(&philo->info->printlock);
	printf("%s %ld %d %s\n", color[x], time, philo->id, state[x]);
	if (x != e_die)
		pthread_mutex_unlock(&philo->info->printlock);
}

t_ms	clock(void)
{
	struct timeval	time;
	long			usec;
	long			sec;
	unsigned long	timenow_us;

	gettimeofday(&time, NULL);
	usec = time.tv_usec;
	sec = time.tv_sec;
	timenow_us = sec * 1000000 + usec;
	return (timenow_us / 1000);
}

t_ms	timestamp(t_philo *philo)
{
	t_ms	timestamp;

	timestamp = clock() - philo->info->starttime;
	return (timestamp);
}
void msleep(int ms)
{
	t_ms max;

	max = clock() + (t_ms)ms;
	while (clock() < max)
		usleep(100);
}
