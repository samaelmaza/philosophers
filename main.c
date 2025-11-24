/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:30:40 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/24 17:46:15 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char *str)
{
	long result;
	long sign;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while(str[i] && str[i] == ' ' || str[i] == '\t')
		i++;
	if(str[i] == '+' || str[i] == '-')
	{
		if(str[i] == '-')
			sign *= -1;
	}
	while(str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i] - '0';
	if(result > INT_MAX)
	{
		printf("The value is not an int\n");
		return (-1);
	}
	return (result * sign);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] == ' ' || str[i] == '\t')
		i++;
	if(str[i] == '+')
		i++;
	if(str[i] == '-')
	{
		printf("Negative numbers are not accepted\n");
		return -1;
	}
	while(str[i])
	{
		if(str[i] > '9' || str[i] < '0')
			return (-1);
		i++;
	}
	return (0);
}

int	parse_input(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	while(i < ac)
	{
		if(is_digit(av[i]) == -1)
			return (1);

		i++;
	}
	return (0);
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
