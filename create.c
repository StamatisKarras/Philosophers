/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:17:51 by skarras           #+#    #+#             */
/*   Updated: 2025/05/05 12:17:41 by skarras          ###   ########.fr       */
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
	int	i;
	int	check;

	locks = (pthread_mutex_t *) malloc(len * sizeof(pthread_mutex_t));
	if (!locks)
		return (NULL);
	i = 0;
	while (i < len)
	{
		check = pthread_mutex_init(&locks[i], NULL);
		if (check != 0)
		{
			free(locks);
			return (NULL);
		}
		i++;
	}
	return (locks);
}

void	delete_locks(pthread_mutex_t *locks, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&locks[i]);
		i++;
	}
	free(locks);
}

void	create_threads(t_info *info)
{
	int				i;

	i = 0;
	info->sync = 0;
	while (i < info->n_philo)
	{
		pthread_create(&info->threads[i], NULL, &routine, (void *) &info->philo[i]);
		i++;
	}
	info->sync = 1;
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

void	assign_locks(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->print_lock, NULL);
	while (i < info->n_philo)
	{
		info->philo[i].right = &info->locks[i];
		if (i - 1 < 0)
			info->philo[i].left = &info->locks[info->n_philo - 1];
		else
			info->philo[i].left = &info->locks[i - 1];
		info->philo[i].print_lock = &info->print_lock;
		i++;
	}
}

void	parse_info_to_philo(char *argv[], t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].id = i;
		info->philo[i].meals_eaten = 0;
		info->philo[i].time_to_die = atoi(argv[2]);
		info->philo[i].time_to_eat = atoi(argv[3]);
		info->philo[i].time_to_sleep = atoi(argv[4]);
		info->philo[i].sync = &info->sync;
		if (i == info->n_philo - 1 && info->n_philo % 2 != 0)
			info->philo[i].odd = 1;
		else
			info->philo[i].odd = 0;
		if (!argv[5])
			info->philo[i].max_meals = -1;
		else
			info->philo[i].max_meals = atoi(argv[5]);
		i++;
	}
}
