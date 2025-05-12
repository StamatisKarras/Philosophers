/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:02 by skarras           #+#    #+#             */
/*   Updated: 2025/05/12 12:08:08 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	if (take_fork(philo) == -1)
	{
		usleep(philo->time_to_die * 1000);
		return ;
	}
	pthread_mutex_lock(philo->sync_lock);
	gettimeofday(&philo->last_meal, NULL);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->sync_lock);
	message("is eating", philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
}

void	p_sleep(t_philo *philo)
{
	message("is sleeping", philo);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	message("is thinking", philo);
	usleep(1000);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		message("has taken a fork", philo);
		if (philo->left == philo->right)
		{
			pthread_mutex_unlock(philo->right);
			return (-1);
		}
		pthread_mutex_lock(philo->left);
		message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->left);
		message("has taken a fork", philo);
		if (philo->left == philo->right)
		{
			pthread_mutex_unlock(philo->left);
			return (-1);
		}
		pthread_mutex_lock(philo->right);
		message("has taken a fork", philo);
	}
	return (0);
}
