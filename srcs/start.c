/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_observer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:02:56 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/02 20:42:02 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].thread, NULL, dinner,
			&table->philos[i]);
		i++;
		usleep(30);
	}
}

void	wait_dinner_end(t_table *table)
{
	int			i;
	pthread_t	thread_observer;

	i = 0;
	pthread_create(&thread_observer, NULL, start_state_observer, table);
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(thread_observer, NULL);
	free(table->fork_status);
	free(table->fork_mutex);
	free(table->logger_mutex);
	free(table->global_mutex);
	free(table->race_mutex);
	free(table->eat_mutex);
	free(table->philos);
	free(table);
}
