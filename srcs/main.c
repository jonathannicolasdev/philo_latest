/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:39:52 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/22 13:00:21 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	if (argc > 4 && argc <= 6)
	{
		if (ft_atoi(argv[1]) < 1)
			return (printf("There must be at least 1 philosopher.\n"));
		if (ft_atoi(argv[2]) < 1)
			return (printf("Time to die must be at least 1.\n"));
		if (ft_atoi(argv[3]) < 1)
			return (printf("Time to eat must be at least 1.\n"));
		if (ft_atoi(argv[4]) < 1)
			return (printf("Time to sleep must be at least 1.\n"));
		if (argc == 6 && ft_atoi(argv[5]) < 1)
			return (printf("Number of times each philosopher must eat must be \
at least 1.\n"));
	}
	else
		return (printf("Input the following arguments: [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep]\n and the Optional input :	\
[number_of_times_each_philosopher_must_eat]\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (check_args(argc, argv) != 0)
		return (1);
	table = create_table(argc, argv);
	start_dinner(table);
	wait_dinner_end(table);
}
