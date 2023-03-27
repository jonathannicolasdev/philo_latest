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

void	unlock_all_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_unlock(&(table->fork_mutex[i]));
		i++;
	}
}

void	start_state_observer(t_table *table)
{
	int			i;
	long long	eat_expire_time;

	sleep(3);
	i = 0;
	while (table->dinner_inprogress)
	{
		while (i < table->nb_philo)
		{
			if (table->philos[i].eat_clock == -1)
				break ;
			eat_expire_time = get_time_in_ms() - table->philos[i].eat_clock;
			if (eat_expire_time > table->todie_time)
			{
				log_status(&(table->philos[i]), " died");
				table->dinner_inprogress = 0;
				exit(0);
			}
			i++;
		}
		usleep(10);
	}
}
