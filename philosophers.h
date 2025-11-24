/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:35:48 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/24 17:32:39 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>

typedef	struct s_philo t_philo;
typedef	struct s_data t_data;

typedef struct s_philosophers
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	pthread_mutex_t *meal_mutex;
	t_data			*data;
};

typedef	struct s_data
{
	int				n_philo;
	long			t_eat;
	long			t_sleep;
	long			t_die;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t print_mutex;
	t_philo			*philos;
	long			start_time;
};

#endif
