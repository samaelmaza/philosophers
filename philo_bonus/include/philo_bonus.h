/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:51:25 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 08:40:09 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/mman.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <limits.h>

/* Gestion de la compatibilité pour mmap */
# ifndef MAP_ANONYMOUS
#  define MAP_ANONYMOUS 0x20
# endif

typedef struct s_program	t_program;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	size_t		last_meal;
	int			meals_eaten;
	pthread_t	thread_id;
	t_program	*program;
}	t_philo;

typedef struct s_program
{
	int			nb_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meals_required;
	size_t		start_time;
	sem_t		*forks;
	sem_t		*write_lock;
	sem_t		*dead_lock;
	sem_t		*meal_lock;
	t_philo		*philos;
}	t_program;

size_t		get_current_time(void);
void		ft_usleep(size_t milliseconds);
int			ft_atoi(char *str);
void		print_message(char *str, t_philo *philo);
int			init_program(t_program *program, char **argv);
void		init_philos(t_program *program);
int			init_semaphores(t_program *program);
void		destroy_all(t_program *program);
int			start_simulation(t_program *program);
int			is_not_valid_input(char **argv, int argc);
void		kill_all_philos(t_program *data);
void		clean_exit(t_program *data);
#endif
