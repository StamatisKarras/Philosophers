/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:01 by skarras           #+#    #+#             */
/*   Updated: 2025/05/13 10:22:27 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	while (ready(philo) == 0)
		usleep(5);
	pthread_mutex_lock(philo->sync_lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(philo->sync_lock);
	actions(philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *) arg;
	while (ready(&info->philo[0]) == 0)
		usleep(5);
	usleep(2 * 1000);
	while (1) //Maybe do while(locks) or  while (philos) so that when my program frees everything the monitoring thread stops.
	{
		if (i == info->n_philo)
			i = 0;
		if (is_dead(&info->philo[i]) == -1)
		{
			pthread_mutex_lock(&info->sync_lock);
			info->sync = -1;
			pthread_mutex_unlock(&info->sync_lock);
			death_message(&info->philo[i]);
			break ;
		}
		i++;
	}
	return (NULL);
}

void	actions(t_philo *philo)
{
	if (philo->id % 2 != 0 || philo->odd == 1)
		think(philo);
	while (1)
	{
		eat(philo);
		p_sleep(philo);
		think(philo);
		pthread_mutex_lock(philo->sync_lock);
		if (philo->meals_eaten == philo->max_meals)
		{
			pthread_mutex_unlock(philo->sync_lock);
			break ;
		}
		pthread_mutex_unlock(philo->sync_lock);
		if (ready(philo) == -1)
			break ;
	}
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
