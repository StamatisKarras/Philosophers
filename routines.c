/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:01 by skarras           #+#    #+#             */
/*   Updated: 2025/05/02 12:20:55 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	//if (philo->id % 2 != 0)
	odd(philo);
	//else
	//	even();
	return (NULL);
}

void	odd(t_philo *philo)
{
	eat(philo);
	//sleep();
	//think();
}
