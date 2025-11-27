/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:29:31 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/27 21:48:37 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo);
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo);
	philo->last_meal = get_current_time();
	print_message("is eating", philo);
	philo->meals_eaten++;
	ft_usleep(philo->program->time_to_eat);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
}
void	child_process(t_philo *philo)
{
	pthread_t	monitor_thread;

	philo->last_meal = get_current_time();
	if(pthread_create(&monitor_thread, NULL, &monitor_routine, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);
	if(philo->id % 2 == 0)
		ft_usleep(1);
	while(1)
	{
		eat(philo);
		print_message("is sleeping", philo);
		ft_usleep(philo->program->time_to_sleep);
		print_message("is thinking", philo);
		usleep(500);
	}
}

void	kill_all_children(t_program *program)
{
	int	i;

	i = 0;
	while(i < program->nb_philos)
	{
		kill(program->philos[i].pid, SIGKILL);
		i++;
	}
}

void	global_monitor(t_program *program)
{
	int		status;
	int		finish_count;
	pid_t	pid;

	finish_count = 0;
	while(finish_count < program->nb_philos)
	{
		pid = waitpid(-1, &status, 0);
		if(pid == -1)
			break;
		if(WIFEXITED(status))
		{
			if(WEXITSTATUS(status) == 1)
			{
				kill_all_children(program);
				return ;
			}
			if(WEXITSTATUS(status) == 0)
				finish_count++;
		}
	}
}
/* Fichier: process_bonus.c ou util_bonus.c */

void	wait_for_zombies(t_program *program)
{
	int	i;
	int	status;

	i = 0;
	while (i < program->nb_philos)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
int	start_simulation(t_program *program)
{
	int	i;

	i = 0;
	while(i < program->nb_philos)
	{
		program->philos[i].pid = fork();
		if(program->philos[i].pid == -1)
			return (printf("Error: Fork failed\n"), 1);
		if(program->philos[i].pid == 0)
		{
			child_process(&program->philos[i]);
			exit(0);
		}
		i++;
	}
	global_monitor(program);
	wait_for_zombies(program);
	return (0);
}
