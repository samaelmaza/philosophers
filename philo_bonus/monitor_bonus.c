/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:41 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/26 23:39:42 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_all_ate(philos) == 1)
			break ;
		i = 0;
		while (i < philos[0].num_of_philos)
		{
			if (philosopher_dead(&philos[i], philos[i].time_to_die))
			{
				print_message("died", &philos[i], philos[i].id);
				pthread_mutex_lock(philos[0].dead_lock);
				*philos->dead = 1;
				pthread_mutex_unlock(philos[0].dead_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
