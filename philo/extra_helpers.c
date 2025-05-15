/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:17:45 by skarras           #+#    #+#             */
/*   Updated: 2025/05/15 10:18:27 by skarras          ###   ########.fr       */
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
