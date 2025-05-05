/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:02 by skarras           #+#    #+#             */
/*   Updated: 2025/05/05 12:54:50 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print_lock);
	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n", ms_calc(&philo->start, &tv), philo->id);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_eat * 1000);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	p_sleep(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(philo->print_lock);
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", ms_calc(&philo->start, &tv), philo->id);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(philo->print_lock);
	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", ms_calc(&philo->start, &tv), philo->id);
	pthread_mutex_unlock(philo->print_lock);
	usleep(1);
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
