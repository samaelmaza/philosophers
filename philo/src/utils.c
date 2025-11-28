/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:44:51 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 18:15:09 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res * sign > INT_MAX)
		return (-1);
	return (res * sign);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday error\n", 19);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void print_message(char *str, t_philo *philo, int id)
{
    size_t  time;

    // 1. On verrouille l'écriture pour que le message ne soit pas coupé
    pthread_mutex_lock(philo->write_lock);

    // 2. On verrouille le dead_lock POUR LIRE LA VALEUR
    pthread_mutex_lock(philo->dead_lock);
    if (!(*philo->dead)) // Maintenant la lecture est protégée
    {
        // On peut déverrouiller dead_lock ici car on est déjà dans le if
        // (Ou après le printf, peu importe tant que write_lock est tenu)
        pthread_mutex_unlock(philo->dead_lock);

        time = get_current_time() - philo->start_time;
        printf("%zu %d %s\n", time, id, str);
    }
    else
    {
        // Si on est mort, on n'oublie pas de déverrouiller
        pthread_mutex_unlock(philo->dead_lock);
    }

    // 3. On libère l'écriture
    pthread_mutex_unlock(philo->write_lock);
}
