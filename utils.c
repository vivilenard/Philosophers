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
	pthread_mutex_lock(&philo->info->printlock);
	t_ms time;

	time = timestamp(philo);
	if (x == e_fork)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (x == e_eat)
		printf("%ld %d is eating\n", time, philo->id);
	else if (x == e_sleep)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (x == e_think)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (x == e_die)
		printf("%ld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->printlock);
}

t_ms clock()
{
	struct timeval 	time;
	long 			usec;
	long 			sec;
	unsigned long	timenow_us;

	gettimeofday(&time, NULL);
	usec = time.tv_usec;
	sec = time.tv_sec;
	timenow_us = sec * 1000000 + usec;
	//printf("sec %ld, usec %ld\n, now %ld", sec, usec, timenow);
	return (timenow_us / 1000);
}

t_ms	timestamp(t_philo *philo)
{
	t_ms	timestamp;

	timestamp = clock() - philo->info->starttime;
	return (timestamp);
}