/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_observer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:02:56 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/22 16:28:43 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_status	check_status(t_philo *philo)
{
	return (philo->status);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].thread, NULL, dinner,
			&table->philos[i]);
		i++;
	}
}

void	wait_dinner_end(t_table *table)
{
	int	i;

	i = 0;
    start_state_observer(table);
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		printf("philos %d finished\n", i);
		i++;
	}
	free(table->fork_mutex);
	free(table->logger_mutex);
	free(table->philos);
	free(table);
}