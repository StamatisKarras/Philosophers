/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:44:05 by skarras           #+#    #+#             */
/*   Updated: 2025/05/08 11:44:42 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	free_everything(t_info *info)
{
	free(info->philo);
	free(info->threads);
}
