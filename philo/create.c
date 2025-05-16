/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:17:51 by skarras           #+#    #+#             */
/*   Updated: 2025/05/16 15:21:41 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philos(int len)
{
	t_philo	*philo;

	philo = (t_philo *) malloc(len * sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, len);
	return (philo);
}

pthread_mutex_t	*create_locks(int len)
{
	pthread_mutex_t	*locks;
	int				i;

	locks = (pthread_mutex_t *) malloc(len * sizeof(pthread_mutex_t));
	if (!locks)
		return (NULL);
	i = 0;
	while (i < len)
	{
		pthread_mutex_init(&locks[i], NULL);
		i++;
	}
	return (locks);
}

void	create_threads(t_info *info)
{
	int				i;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_create(&info->threads[i], NULL, &routine,
				(void *) &info->philo[i]) != 0)
		{
			stop_error(i - 1, info);
			return ;
		}
		i++;
	}
	pthread_mutex_lock(&info->sync_lock);
	gettimeofday(&info->start, NULL);
	info->sync = 1;
	pthread_mutex_unlock(&info->sync_lock);
	pthread_create(&info->all_seeing, NULL, &monitor, (void *) info);
	pthread_detach(info->all_seeing);
	i = 0;
	while (i < info->n_philo)
	{
		pthread_join(info->threads[i], NULL);
		i++;
	}
}

pthread_t	*allocate_threads(int len)
{
	pthread_t	*threads;

	threads = (pthread_t *) malloc(len * sizeof(pthread_t));
	if (!threads)
		return (NULL);
	memset(threads, 0, len);
	return (threads);
}
