/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:59:01 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/18 15:23:11 by vlenard          ###   ########.fr       */
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

void	printstate(t_philo *philo, int x)
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
	if (x == 1)
		printf("%s %ld %d %s\n", color[x], philo->last_meal, philo->id, state[x]);
	else
		printf("%s %ld %d %s\n", color[x], timestamp(philo), philo->id, state[x]);
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
	//printf("sec %ld, usec %ld\n, now %ld", sec, usec, timenow);

t_ms	timestamp(t_philo *philo)
{
	t_ms	timestamp;

	timestamp = clock() - philo->info->starttime;
	return (timestamp);
}
