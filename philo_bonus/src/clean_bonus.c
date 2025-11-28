/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:14 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 08:27:22 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphores(t_program *program)
{
	sem_close(program->forks);
	sem_close(program->dead_lock);
	sem_close(program->write_lock);
	sem_close(program->meal_lock);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_dead");
	sem_unlink("/philo_meal");
}

void	destroy_all(t_program *program)
{
	size_t	size_philo_arr;

	destroy_semaphores(program);
	size_philo_arr = sizeof(t_philo) * program->nb_philos;
	if (program->philos)
		munmap(program->philos, size_philo_arr);
	if (program)
		munmap(program, sizeof(t_program));
}

void	kill_all_philos(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	clean_exit(t_program *data)
{
	sem_close(data->forks);
	sem_close(data->write_lock);
	sem_close(data->meal_lock);
	sem_close(data->dead_lock);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_meal");
	sem_unlink("/philo_stop");
	if (data->philos)
		free(data->philos);
}
