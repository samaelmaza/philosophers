/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:29:31 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 15:07:38 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*monitor_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->program->meal_lock);
		if (get_current_time() - philo->last_meal > philo->program->time_to_die)
		{
			sem_wait(philo->program->write_lock);
			printf("%ld %d died\n", get_current_time()
				- philo->program->start_time,
				philo->id);
			sem_post(philo->program->meal_lock);
			exit(1);
		}
		sem_post(philo->program->meal_lock);
		if (philo->program->meals_required != -1
			&& philo->meals_eaten >= philo->program->meals_required)
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	eat(t_philo	*philo)
{
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo);
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo);
	print_message("is eating", philo);
	sem_wait(philo->program->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->program->meal_lock);
	ft_usleep(philo->program->time_to_eat);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &monitor_thread, philo);
	pthread_detach(monitor);
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		eat(philo);
		if (philo->program->meals_required != -1
			&& philo->meals_eaten >= philo->program->meals_required)
			exit(0);
		print_message("is sleeping", philo);
		ft_usleep(philo->program->time_to_sleep);
		print_message("is thinking", philo);
	}
}

int	init_processes(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (1);
		if (data->philos[i].pid == 0)
			philo_routine(&data->philos[i]);
		i++;
	}
	return (0);
}

int	start_simulation(t_program *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			philo_routine(&data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all_philos(data);
			i = data->nb_philos;
		}
		i++;
	}
	destroy_all(data);
	return (0);
}
