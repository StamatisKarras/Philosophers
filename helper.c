/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:09:12 by skarras           #+#    #+#             */
/*   Updated: 2025/05/07 11:40:00 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	long			ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = ms_calc(&philo->last_meal, &tv);
	if (ms >= philo->time_to_die)
		return (-1);
	return (0);
}

void	message(char *message, t_philo *philo)
{
	struct timeval tv;
	long			ms;

	if (*philo->sync == -1)
	{
		pthread_mutex_unlock(philo->print_lock);
		return ;
	}
	gettimeofday(&tv, NULL);
	ms = ms_calc(&philo->start, &tv);
	printf("%ld %d %s\n", ms, philo->id, message);
}

void	death_message(t_philo *philo)
{
	struct timeval tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = ms_calc(&philo->start, &tv);
	printf("%ld %d died\n", ms, philo->id);
}

void	free_everything(t_info *info)
{
	free(info->philo);
	free(info->threads);
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
