/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:01 by skarras           #+#    #+#             */
/*   Updated: 2025/05/08 13:03:35 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	tv;

	philo = (t_philo *) arg;
	while (philo->sync == 0)
		usleep(0);
	gettimeofday(&tv, NULL);
	gettimeofday(&philo->last_meal, NULL);
	philo->start = tv;
	actions(philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *) arg;
	while (info->sync == 0)
		usleep(0);
	usleep(2 * 1000);
	while (1)
	{
		if (i == info->n_philo - 1)
			i = 0;
		if (is_dead(&info->philo[i]) == -1)
		{
			info->sync = -1;
			pthread_mutex_lock(&info->print_lock);
			death_message(&info->philo[i]);
			pthread_mutex_unlock(&info->print_lock);
			break ;
		}
	}
	return (NULL);
}

void	actions(t_philo *philo)
{
	if (philo->id % 2 != 0 || philo->odd == 1)
		think(philo);
	while (1)
	{
		if (philo->meals_eaten == philo->max_meals)
			break ;
		eat(philo);
		p_sleep(philo);
		think(philo);
		if (*philo->sync == -1)
			break ;
	}
}
