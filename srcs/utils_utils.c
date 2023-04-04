/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:40:07 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/02 20:53:00 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_eat_clock(int num_philo, long long value, t_table *table)
{
	pthread_mutex_lock(table->race_mutex);
	table->philos[num_philo].eat_clock = value;
	pthread_mutex_unlock(table->race_mutex);
}

long long read_eat_clock(int num_philo, t_table *table)
{
	long long value;

	pthread_mutex_lock(table->race_mutex);
	value = table->philos[num_philo].eat_clock;
	pthread_mutex_unlock(table->race_mutex);
	return (value);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	sleep_duration(long long duration)
{
	long long	start;
	long long	end;

	start = get_time_in_ms();
	while (1)
	{
		end = get_time_in_ms();
		if ((end - start) >= duration)
			break ;
		usleep(30);
	}
}

void	log_status(t_philo *philo, char *str)
{
	long long	time_in_ms;

	pthread_mutex_lock(philo->table->logger_mutex);
	time_in_ms = get_time_in_ms() - philo->table->launch_time;
	printf("%lld %d %s\n", time_in_ms, philo->num, str);
	pthread_mutex_unlock(philo->table->logger_mutex);
}
