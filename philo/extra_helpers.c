/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:17:45 by skarras           #+#    #+#             */
/*   Updated: 2025/05/19 09:56:26 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	should_start(t_info *info)
{
	int	i;
	int	count;
	int	n_philo;

	pthread_mutex_lock(&info->sync_lock);
	n_philo = info->n_philo;
	pthread_mutex_unlock(&info->sync_lock);
	count = 0;
	while (count < n_philo)
	{
		i = 0;
		while (i < n_philo)
		{
			usleep(1000);
			pthread_mutex_lock(&info->sync_lock);
			if (info->philo[i].started == 1)
			{
				info->philo[i].started = -1;
				count++;
			}
			pthread_mutex_unlock(&info->sync_lock);
			i++;
		}
	}
}

int	check_quit(t_info *info)
{
	pthread_mutex_lock(&info->sync_lock);
	if (info->sync == 2)
		return (-1);
	pthread_mutex_unlock(&info->sync_lock);
	return (0);
}

int	ready(t_philo *philo)
{
	pthread_mutex_lock(philo->sync_lock);
	if (*philo->sync == 1)
	{
		pthread_mutex_unlock(philo->sync_lock);
		return (1);
	}
	else if (*philo->sync == -1)
	{
		pthread_mutex_unlock(philo->sync_lock);
		return (-1);
	}
	pthread_mutex_unlock(philo->sync_lock);
	return (0);
}

int	check_if_not_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

void	custom_sleep(long time, t_philo *philo)
{
	struct timeval	start;
	struct timeval	end;
	long			time_passed;

	time_passed = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		time_passed = ms_calc(&start, &end);
		if (time_passed >= time)
			break ;
		usleep(1000);
		pthread_mutex_lock(philo->sync_lock);
		if (*philo->sync == -1)
		{
			pthread_mutex_unlock(philo->sync_lock);
			return ;
		}
		pthread_mutex_unlock(philo->sync_lock);
	}
}
