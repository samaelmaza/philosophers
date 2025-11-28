/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:47 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/28 15:00:16 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	is_not_digit(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] && (av[i][j] == ' '
			|| (av[i][j] >= 9 && av[i][j] <= 13)))
			j++;
		if (av[i][j] == '-')
			return (printf("Error: cannot be negative\n"), 1);
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (printf("Error: a letter has been detected\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_empty(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] && (av[i][j] == ' '
			|| (av[i][j] >= 9 && av[i][j] <= 13)))
			j++;
		if (av[i][j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	input_is_not_valid(char **av)
{
	if (ft_atoi(av[2]) == -1
		|| ft_atoi(av[3]) == -1
		|| ft_atoi(av[4]) == -1)
		return (printf("Error: argument has to be an int\n"), -1);
	if (ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) < 60)
		return (printf("Values cannot be below 60ms\n"), -1);
	return (0);
}

int	is_not_valid_input(char **argv, int argc)
{
	if (is_not_digit(argv, argc))
		return (1);
	if (is_empty(argv, argc))
		return (printf("Error: empty value\n"), 1);
	if (input_is_not_valid(argv) == -1)
		return (1);
	return (0);
}
