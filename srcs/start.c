/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:19:48 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/16 17:46:33 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dinner(t_table *table)
{
	int		i;
	//void	*philo_v;

	i = 0;
	table->launch_time = ft_get_time();
	while (i < table->nb_philo)
	{
		//philo_v = (void *)&(philo[i]);
		//if (pthread_create(&(philo[i].thread), NULL, dinner, philo_v) == -1)
		//	printf("failed to create the thread");
		if (pthread_create(&table->philos[i].thread, NULL, dinner, &table->philos[i]) == -1)
			printf("failed to create the thread");
		i++;
	}
	ft_wait(table, table->eat_time);
	ft_check_die(table);
	return (0);
}

void	ft_check_die(t_table *table)
{
	while (table->is_all_safe)
	{
		pthread_mutex_lock(&(table->eat));
		if (check_eat_time(table))
			break ;
		if (table->must_eat_num != -1)
			if (check_eat_num(table))
				break ;
		pthread_mutex_unlock(&(table->eat));
	}
	printf("we are here");
	pthread_mutex_unlock(&(table->eat));
	wait_dinner_end(table);
}

int	check_eat_time(t_table *table)
{
	long long	time;
	int			i;

	i = 0;
	while (i < table->nb_philo)
	{
		time = ft_get_time() - table->launch_time;
		if ((time - table->philos[i].last_eat_time) > table->todie_time)
		{
			pthread_mutex_lock(table->logger_mutex);
			table->is_all_safe = 0;
			printf("this philo is dead");
			pthread_mutex_unlock(table->logger_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_eat_num(t_table *table)
{
	long long	time;
	int			i;
	int			total;

	i = 0;
	total = 0;
	while (i < table->nb_philo)
	{
		if (table->philos[i].number_of_meals >= table->must_eat_num
			&& table->must_eat_num != 1)
			total++;
		i++;
	}
	if (total == table->must_eat_num)
	{
		pthread_mutex_lock(table->logger_mutex);
		table->is_all_safe = 0;
		time = ft_get_time() - table->launch_time;
		printf("they all ate");
		pthread_mutex_unlock(table->logger_mutex);
		return (1);
	}
	return (0);
}
