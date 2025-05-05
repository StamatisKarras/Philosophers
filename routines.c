/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:01 by skarras           #+#    #+#             */
/*   Updated: 2025/05/05 12:10:07 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval 		tv;

	philo = (t_philo *) arg;
	while (philo->sync == 0)
		usleep(0);
	gettimeofday(&tv, NULL);
	philo->start = tv;
	actions(philo);
	return (NULL);
}

void	actions(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->id % 2 != 0 || philo->odd == 1)
			think(philo);
	while(i < 10)
	{
		eat(philo);
		p_sleep(philo);
		think(philo);
		i++;
	}
}
