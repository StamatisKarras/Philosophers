/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:06:29 by skarras           #+#    #+#             */
/*   Updated: 2025/05/16 14:34:28 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philoshophers(t_info *info, char *argv[])
{
	info->locks = create_locks(info->n_philo);
	if (!info->locks)
		return (-1);
	info->philo = create_philos(info->n_philo);
	if (!info->philo)
	{
		delete_locks(info->locks, info->n_philo);
		return (-1);
	}
	parse_info_to_philo(argv, info);
	assign_locks(info);
	info->threads = allocate_threads(info->n_philo);
	if (!info->threads)
	{
		free(info->philo);
		delete_locks(info->locks, info->n_philo);
		return (-1);
	}
	create_threads(info);
	pthread_mutex_lock(&info->sync_lock);
	info->sync = 2;
	pthread_mutex_unlock(&info->sync_lock);
	delete_locks(info->locks, info->n_philo);
	free_everything(info);
	return (0);
}

int	main(int argc, char *argv[])
{
	int			error;
	t_info		info;

	if (argc == 5 || argc == 6)
	{
		if (check_info(argv, argc) == -1)
		{
			write(2, "ERROR\n", 6);
			return (-1);
		}
		info.n_philo = ft_atoi(argv[1]);
		error = philoshophers(&info, argv);
		if (error == -1)
		{
			write(2, "ERROR\n", 6);
			return (-1);
		}
	}
	else
		write(2, "ERROR\n", 6);
	return (0);
}
