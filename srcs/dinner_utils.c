/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:36:36 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/27 16:16:01 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	write_status(philo->num, THINK, philo->table);
	log_status(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	log_status(philo, "is sleeping");
	sleep_duration(philo->table->sleep_time);
}

int eatcount_constraint(t_philo *philo, t_table *table)
{
	int	number_eats;
	int	counter_eats;

	pthread_mutex_lock(table->race_mutex);
	number_eats = table->number_of_eats;
	counter_eats = philo->counter_of_eats;
	pthread_mutex_unlock(table->race_mutex);
	if (table->number_of_eats > 0 \
		&& philo->counter_of_eats >= table->number_of_eats)
		return (1);
	else
		return (0);
}