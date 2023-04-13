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

void	printstate(t_philo *philo, int x, int id)
{
	pthread_mutex_lock(&philo->shared->printlock);
	t_us time;

	time = clock() - philo->params->starttime;
	if (x == e_fork)
		printf("%ld %d has taken a fork %d\n", time, philo->id, id);
	if (x == e_rightfork)
		printf("%ld %d has taken a rightfork %d\n", time, philo->id, id);
	else if (x == e_eat)
		printf("%ld %d is eating\n", time, philo->id);
	else if (x == e_sleep)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (x == e_think)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (x == e_downfork)
			printf("%ld %d put down fork\n", time, philo->id);
	else if (x == e_downrightfork)
		printf("%ld %d put down right fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->shared->printlock);
}
