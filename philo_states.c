/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:02 by skarras           #+#    #+#             */
/*   Updated: 2025/05/08 13:13:47 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	message("has taken a fork", philo);
	if (philo->left == philo->right)
	{
		pthread_mutex_unlock(philo->left);
		return ;
	}
	pthread_mutex_lock(philo->right);
	message("has taken a fork", philo);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_lock(philo->print_lock);
	message("is eating", philo);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	message("is sleeping", philo);
	pthread_mutex_unlock(philo->print_lock);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	message("is thinking", philo);
	pthread_mutex_unlock(philo->print_lock);
	usleep(1);
}
