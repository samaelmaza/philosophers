/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:28 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/26 23:39:30 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong argument count\n"), 1);
	if(is_not_valid_input(argv, argc))
		return (1);
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if(!philos || !forks)
		return (printf("Error: Malloc failed\n"), 1);
	init_program(philos, &program);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program);
	destroy_all(NULL, &program, forks);
	return (0);
}
