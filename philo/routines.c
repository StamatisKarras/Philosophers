/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:01 by skarras           #+#    #+#             */
/*   Updated: 2025/05/15 10:21:08 by skarras          ###   ########.fr       */
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
	philo->started = 1;
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
	should_start(info);
	while (1)
	{
		check_quit(info);
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
