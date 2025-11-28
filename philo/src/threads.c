/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:45:51 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 18:15:04 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	// 1. DÉCIDER L'ORDRE POUR ÉVITER LE DEADLOCK (ET HELGRIND)
	// Si id est pair : Droite puis Gauche
	// Si id est impair : Gauche puis Droite
	if (philo->id % 2 == 0)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}

	// 2. PRENDRE LA PREMIÈRE
	pthread_mutex_lock(first_fork);
	print_message("has taken a fork", philo, philo->id);

	// 3. GÉRER LE CAS DU PHILO SEUL (Important !)
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(first_fork);
		return ;
	}

	// 4. PRENDRE LA SECONDE
	pthread_mutex_lock(second_fork);
	print_message("has taken a fork", philo, philo->id);

	// 5. CHECK MORT AVANT DE MANGER (Sécurité)
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(first_fork); // Attention à déverrouiller dans l'ordre inverse
		pthread_mutex_unlock(second_fork);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);

	// 6. MANGER
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);

	ft_usleep(philo->time_to_eat);
	philo->eating = 0;

	// 7. LIBÉRER (Toujours les deux)
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_dead(philo))
	{
		eat(philo);
		print_message("is sleeping", philo, philo->id);
		ft_usleep(philo->time_to_sleep);
		print_message("is thinking", philo, philo->id);
		if (philo->num_of_philos % 2 != 0)
			ft_usleep(1);
	}
	return (pointer);
}

int	thread_create(t_program *program)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		return (1);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		return (1);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
