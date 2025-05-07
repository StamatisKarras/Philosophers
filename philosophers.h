/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarras <skarras@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:00:27 by skarras           #+#    #+#             */
/*   Updated: 2025/05/07 11:52:14 by skarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	struct			timeval start;
	struct			timeval last_meal;
	int				*sync;
	int				odd;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

typedef struct s_info
{
	pthread_mutex_t	*locks;
	pthread_mutex_t	print_lock;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_t		all_seeing;
	int				n_philo;
	int				sync;
}	t_info;

pthread_mutex_t	*create_locks(int len);
t_philo			*create_philos(int len);
void			assign_locks(t_info *info);
pthread_t		*allocate_threads(int len);
void			delete_locks(pthread_mutex_t *locks, int len);
void			create_threads(t_info *info);
int				philoshophers(t_info *info, char *argv[]);
void			parse_info_to_philo(char *argv[], t_info *info);
void			*routine(void *arg);
long	ms_calc(struct timeval *start, struct timeval *end);
void	eat(t_philo *philo);
void	actions(t_philo *philo);
void	p_sleep(t_philo *philo);
void	think(t_philo *philo);
void	message(char *message, t_philo *philo);
void	*monitor(void *arg);
int	is_dead(t_philo *philo);
void	death_message(t_philo *philo);
void	free_everything(t_info *info);

#endif
