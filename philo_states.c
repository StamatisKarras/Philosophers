/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:02 by skarras           #+#    #+#             */
/*   Updated: 2025/05/02 11:51:17 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	struct timeval tv;
	long			elapsed;

	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	gettimeofday(&tv, NULL);
	elapsed = ms_calc(&philo->start, &tv);
	printf("%ld %d is eating\n", elapsed, philo->id);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

long	ms_calc(struct timeval *start, struct timeval *end)
{
	long	seconds;
	long	microseconds;
	long	elapsed;

	seconds = end->tv_sec - start->tv_sec;
	microseconds = end->tv_usec - start->tv_usec;
	elapsed = (seconds * 1000) + (microseconds / 1000);
	return (elapsed);
}
