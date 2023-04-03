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

int	ft_atoi(const char *nptr)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		nptr++;
	if (nptr[i] == '-')
		sign = sign * -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		nptr++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + nptr[i] - '0';
		nptr++;
		if (num * sign > 2147483647)
			return (-1);
		if (num * sign < -2147483648)
			return (0);
	}
	return (num * sign);
}
/*
void	print_dead(t_philo *philo)
{
	printf("%d", philo->num);
}
*/

int	round_left(int index, int n)
{
	if ((index - 1) < 0)
		return (n - 1);
	else
		return (index - 1);
}

int	round_right(int index, int n)
{
	if ((index + 1) == n)
		return (0);
	else
		return (index + 1);
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

void	write_status(int num_philo, t_status value, t_table *table)
{
	pthread_mutex_lock(table->race_mutex);
	table->philos[num_philo].status = value;
	pthread_mutex_unlock(table->race_mutex);
}

t_status	read_status(int num_philo, t_table *table)
{
	t_status	value;

	pthread_mutex_lock(table->race_mutex);
	value = table->philos[num_philo].status;
	pthread_mutex_unlock(table->race_mutex);
	return (value);
}

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

void write_dinner_inprogress(int value, t_table *table)
{
	pthread_mutex_lock(table->race_mutex);
	table->dinner_inprogress = value;
	pthread_mutex_unlock(table->race_mutex);
}

int read_dinner_inprogress(t_table *table)
{
	int value;

	pthread_mutex_lock(table->race_mutex);
	value = table->dinner_inprogress;
	pthread_mutex_unlock(table->race_mutex);
	return (value);
}