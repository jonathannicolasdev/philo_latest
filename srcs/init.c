/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:37:00 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/22 15:44:27 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_table *table)
{
	int				i;
	pthread_mutex_t	*fork_mutex;
	t_fork_status	*fork_status;

	fork_mutex = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	fork_status = malloc(sizeof(t_fork_status) * table->nb_philo);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&fork_mutex[i], NULL);
		pthread_mutex_lock(&fork_mutex[i]);
		fork_status[i] = FREE;
		i++;
	}
	table->fork_mutex = fork_mutex;
	table->fork_status = fork_status;
}

void	seat_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->nb_philo);
	while (i < table->nb_philo)
	{
		philos[i].num = i;
		philos[i].counter_of_eats = 0;
		philos[i].left_fork = i;
		philos[i].right_fork = round_right(i, table->nb_philo);
		philos[i].table = table;
		philos[i].status = THINK;
		philos[i].die_clock = -1;
		philos[i].eat_clock = -1;
		philos[i].sleep_clock = -1;
		i++;
	}
	table->philos = philos;
}

t_table	*create_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->nb_philo = ft_atoi(argv[1]);
	table->todie_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	if (!argv[5])
		table->number_of_eats = -1;
	else
		table->number_of_eats = ft_atoi(argv[5]);
	table->launch_time = get_time_in_ms();
	table->dinner_inprogress = 1;
	put_forks(table);
	init_logger(table);
	init_global_mutex(table);
	init_race_mutex(table);
	seat_philos(table);
	return (table);
}
