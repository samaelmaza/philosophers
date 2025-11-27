/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:39:28 by sreffers          #+#    #+#             */
/*   Updated: 2025/11/27 20:45:25 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	safe_exit(t_program *program)
{
	destroy_all(program);
	if (program)
		munmap(program, sizeof(t_program));
}

int	main(int argc, char **argv)
{
	t_program		*program;

	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong argument count\n"), 1);
	if(ft_atoi(argv[1]) < 1)
		return (printf("Error: Invalid number of philosophers\n"), 1);
	if(is_not_valid_input(argv, argc))
		return (1);
	program = mmap(NULL, sizeof(t_program), PROT_READ | PROT_WRITE,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(program == MAP_FAILED)
		return (printf("Error: Mmap failed\n"), 1);
	if(init_program(program, argv) != 0)
		return (safe_exit(program),1);
	if(start_simulation(program) != 0)
		return (safe_exit(program), 1);
	safe_exit(program);
	return (0);
}
