/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:41 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/27 19:44:25 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (get_current_time() - philo->last_meal > philo->program->time_to_die)
		{
			sem_wait(philo->program->write_lock);
			printf("%lld %d died\n",
			get_current_time() - philo->program->start_time,
			philo->id);

			sem_post(philo->program->dead_lock);
			exit(1);
		}
		if (philo->program->meals_required != -1
		&& philo->meals_eaten >= philo->program->meals_required)
		exit(0);
		usleep(1000);
	}
	return (NULL);
}
