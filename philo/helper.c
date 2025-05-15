/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:09:12 by skarras           #+#    #+#             */
/*   Updated: 2025/05/15 10:12:28 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	long			ms;
	struct timeval	tv;

	pthread_mutex_lock(philo->sync_lock);
	if (philo->meals_eaten == philo->max_meals)
	{
		pthread_mutex_unlock(philo->sync_lock);
		return (0);
	}
	gettimeofday(&tv, NULL);
	ms = ms_calc(&philo->last_meal, &tv);
	if (ms >= philo->time_to_die)
	{
		pthread_mutex_unlock(philo->sync_lock);
		return (-1);
	}
	pthread_mutex_unlock(philo->sync_lock);
	return (0);
}

void	message(char *message, t_philo *philo)
{
	struct timeval	tv;
	long			ms;

	if (ready(philo) == -1)
		return ;
	pthread_mutex_lock(philo->sync_lock);
	gettimeofday(&tv, NULL);
	ms = ms_calc(philo->start, &tv);
	printf("%ld %d %s\n", ms, philo->id, message);
	pthread_mutex_unlock(philo->sync_lock);
}

void	death_message(t_philo *philo)
{
	struct timeval	tv;
	long			ms;

	pthread_mutex_lock(philo->sync_lock);
	gettimeofday(&tv, NULL);
	ms = ms_calc(philo->start, &tv);
	printf("%ld %d died\n", ms, philo->id);
	pthread_mutex_unlock(philo->sync_lock);
}

long	ms_calc(struct timeval *start, struct timeval *end)
{
	long	seconds;
	long	microseconds;
	long	elapsed;

	seconds = end->tv_sec - start->tv_sec;
	microseconds = end->tv_usec - start->tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	elapsed = (seconds * 1000) + (microseconds / 1000);
	return (elapsed);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	sign = 0;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (sign == 1)
		res = -res;
	return (res);
}
