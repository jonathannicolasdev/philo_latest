/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:40:07 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/07 18:22:35 by jnicolas         ###   ########.fr       */
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

void	write_fork_status(int fork_id, t_fork_status value, t_table *table)
{
	pthread_mutex_lock(table->race_mutex);
	table->fork_status[fork_id] = value;
	pthread_mutex_unlock(table->race_mutex);
}

t_fork_status	read_fork_status(int fork_id, t_table *table)
{
	t_fork_status	value;

	pthread_mutex_lock(table->race_mutex);
	value = table->fork_status[fork_id];
	pthread_mutex_unlock(table->race_mutex);
	return (value);
}
