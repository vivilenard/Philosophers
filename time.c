/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:40:54 by vlenard           #+#    #+#             */
/*   Updated: 2023/04/23 15:41:05 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "existentialism.h"

t_ms	current_time(void)
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

	timestamp = current_time() - philo->info->starttime;
	return (timestamp);
}

void	msleep(int ms)
{
	t_ms	max;

	max = current_time() + (t_ms)ms;
	while (current_time() < max)
		usleep(100);
}
