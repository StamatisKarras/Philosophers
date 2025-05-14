/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:45:16 by skarras           #+#    #+#             */
/*   Updated: 2025/05/12 11:14:44 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_locks(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->print_lock, NULL);
	pthread_mutex_init(&info->sync_lock, NULL);
	while (i < info->n_philo)
	{
		info->philo[i].right = &info->locks[i];
		if (i - 1 < 0)
			info->philo[i].left = &info->locks[info->n_philo - 1];
		else
			info->philo[i].left = &info->locks[i - 1];
		info->philo[i].print_lock = &info->print_lock;
		info->philo[i].sync_lock = &info->sync_lock;
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
		info->philo[i].time_to_die = ft_atoi(argv[2]);
		info->philo[i].time_to_eat = ft_atoi(argv[3]);
		info->philo[i].time_to_sleep = ft_atoi(argv[4]);
		info->philo[i].sync = &info->sync;
		info->philo[i].start = &info->start;
		if (i == info->n_philo - 1 && info->n_philo % 2 != 0)
			info->philo[i].odd = 1;
		else
			info->philo[i].odd = 0;
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
		if (ft_atoi(argv[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}
