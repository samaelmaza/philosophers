/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:30:40 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/23 23:36:51 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_input(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	while(i < ac)
	{

	}
}
int	main(int ac, char **av)
{
	t_data data;

	if(ac == 5 || ac == 6)
	{
		if(parse_input(&data, ac, av))
		{

		}
	}
	else
	{
		printf("Correct use : ./philo 5 800 200 200 [5]\n");
		return (1);
	}
}
