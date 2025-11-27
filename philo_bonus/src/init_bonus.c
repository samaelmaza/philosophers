/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:22 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/27 21:24:15 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void clean_semaphores()
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_dead");
	sem_unlink("/philo_meal");
}
int	init_semaphores(t_program *program)
{
	clean_semaphores();
	program->forks = sem_open("/philo_forks", O_CREAT, 0664, program->nb_philos);
	program->write_lock = sem_open("/philo_write", O_CREAT, 0644, 1);
	program->dead_lock = sem_open("/philo_dead", O_CREAT, 0644, 1);
	program->meal_lock = sem_open("/philo_meal", O_CREAT, 0644, 1);
	if(program->forks == SEM_FAILED ||
		program->write_lock == SEM_FAILED ||
		program->dead_lock == SEM_FAILED ||
		program->meal_lock == SEM_FAILED)
		return (1);
	return (0);
}

void	init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nb_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = get_current_time();
		program->philos[i].program = program;
		i++;
	}
}

int	init_program(t_program *program, char **argv)
{
	program->nb_philos = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		program->meals_required = ft_atoi(argv[5]);
	else
		program->meals_required = -1;
	program->philos = mmap(NULL, sizeof(t_philo) * program->nb_philos,
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (program->philos == MAP_FAILED)
	{
		printf("Error: Mmap philos failed\n");
		return (1);
	}
	if (init_semaphores(program) != 0)
	{
		munmap(program->philos, sizeof(t_philo) * program->nb_philos);
		return (1);
	}
	init_philos(program);
	return (0);
}
