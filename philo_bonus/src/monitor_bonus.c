/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:41 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/27 21:54:17 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *monitor_routine(void *pointer)
{
    t_philo *philo;
    philo = (t_philo *)pointer;

    while (1)
    {
        if (get_current_time() - philo->last_meal > philo->program->time_to_die)
        {
            sem_wait(philo->program->write_lock);
            printf("%ld %d died\n",
                get_current_time() - philo->program->start_time,
                philo->id);
			sem_post(philo->program->dead_lock);
            exit(1);
        }

        if (philo->program->meals_required != -1
            && philo->meals_eaten >= philo->program->meals_required)
        {
            exit(0);  // ⚠️ Vérifie que c'est bien exit(0), pas exit(1)
        }

        usleep(1000);
    }
    return (NULL);
}
