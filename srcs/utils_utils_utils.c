/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:40:07 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/22 15:47:15 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_dinner_inprogress(int value, t_table *table)
{
	pthread_mutex_lock(table->race_mutex);
	table->dinner_inprogress = value;
	pthread_mutex_unlock(table->race_mutex);
}

int	read_dinner_inprogress(t_table *table)
{
	int	value;

	pthread_mutex_lock(table->race_mutex);
	value = table->dinner_inprogress;
	pthread_mutex_unlock(table->race_mutex);
	return (value);
}

/*
void	print_forks(t_table *table)
{
	int	i;

	printf("\nForks status: ");
	for (i = 0; i < table->nb_philo; i++)
	{
		if (table->fork_status[i] == FREE)
			printf("%2d:free,", i);
		else
			printf("%2d:taken,", i);
	}
	printf("\n");
}
*/