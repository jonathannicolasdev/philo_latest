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

int	timeisup_state_observer(t_table *table)
{
	int			i;
	long long	eat_expire_time;
	long long	eat_clock;

	i = 0;
	while (i < table->nb_philo)
	{
		eat_clock = read_eat_clock(table->philos[i].num, table);
		if (eat_clock == -1)
			break ;
		eat_expire_time = get_time_in_ms() - eat_clock;
		if (eat_expire_time > table->todie_time)
		{
			log_status(&(table->philos[i]), " died");
			write_dinner_inprogress(0, table);
			exit(0);
		}
		i++;
	}
	return (0);
}

int	eat_state_observer(t_table *table)
{
	int			i;
	int			count_eatcount_constraint;
	long long	time;

	i = 0;
	count_eatcount_constraint = 0;
	while (i < table->nb_philo)
	{
		if (eatcount_constraint(&(table->philos[i]), table))
			count_eatcount_constraint++;
		i++ ;
	}
	if (count_eatcount_constraint == table->nb_philo)
	{
		pthread_mutex_lock(table->logger_mutex);
		write_dinner_inprogress(0, table);
		time = get_time_in_ms() - table->launch_time;
		printf("%lldms all philo eat %d time\n", time, table->number_of_eats);
		pthread_mutex_unlock(table->logger_mutex);
		return (1);
	}
	return (0);
}

void	start_state_observer(t_table *table)
{
	while (table->dinner_inprogress)
	{
		if (timeisup_state_observer(table))
			break ;
		if (eat_state_observer(table))
			break ;
		usleep(100);
	}
	unlock_all_forks(table);
}
/*
void	start_state_observer(t_table *table)
{
	int			i;
	long long	eat_expire_time;
	long long	eat_clock;
	int			count_eatcount_constraint;

	while (table->dinner_inprogress)
	{
		i = 0;
		count_eatcount_constraint = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(table->race_mutex);
			eat_clock = table->philos[i].eat_clock;
			pthread_mutex_unlock(table->race_mutex);
			if (eat_clock == -1)
				break ;
			if (eatcount_constraint(&(table->philos[i]), table))
			{
				count_eatcount_constraint++;
				i++ ;
				continue ;
			}
			eat_expire_time = get_time_in_ms() - eat_clock;
			if (eat_expire_time > table->todie_time)
			{
				log_status(&(table->philos[i]), " died");
				table->dinner_inprogress = 0;
				exit(0);
			}
			i++;
		}
		if (count_eatcount_constraint == table->nb_philo)
			break ;
		usleep(100);
	}
	unlock_all_forks(table);
}
*/