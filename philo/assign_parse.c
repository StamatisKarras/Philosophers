/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:45:16 by skarras           #+#    #+#             */
/*   Updated: 2025/05/16 15:57:34 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_locks(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->sync_lock, NULL);
	while (i < info->n_philo)
	{
		info->philo[i].right = &info->locks[i];
		if (i - 1 < 0)
			info->philo[i].left = &info->locks[info->n_philo - 1];
		else
			info->philo[i].left = &info->locks[i - 1];
		info->philo[i].sync_lock = &info->sync_lock;
		i++;
	}
}

void	parse_info_to_philo(char *argv[], t_info *info)
{
	int	i;

	i = 0;
	info->sync = 0;
	info->error = 0;
	while (i < info->n_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].meals_eaten = 0;
		info->philo[i].time_to_die = ft_atoi(argv[2]);
		info->philo[i].time_to_eat = ft_atoi(argv[3]);
		info->philo[i].time_to_sleep = ft_atoi(argv[4]);
		info->philo[i].sync = &info->sync;
		info->philo[i].start = &info->start;
		info->philo[i].started = 0;
		info->philo[i].error = &info->error;
		if (!argv[5])
			info->philo[i].max_meals = -1;
		else
			info->philo[i].max_meals = ft_atoi(argv[5]);
		i++;
	}
}

int	check_info(char *argv[], int n)
{
	int	i;

	i = 1;
	while (i < n)
	{
		if (check_if_not_num(argv[i]) == -1)
			return (-1);
		if (ft_atoi(argv[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}
