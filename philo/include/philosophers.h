/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:44:28 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 08:14:17 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

int		ft_atoi(char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_message(char *str, t_philo *philo, int id);
void	init_program(t_philo *philos, t_program *program);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **argv);
int		thread_create(t_program *program);
void	*monitor(void *pointer);
void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks);
int		is_not_valid_input(char **argv, int argc);

#endif
