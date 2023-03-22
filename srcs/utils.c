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

long long	get_time_in_ms(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	smart_sleep(long long time, t_philo *philo)
{
	// long long	time_in_ms;
	printf("%d %lld", philo->num, time);
	// time_in_ms = get_time_in_ms();
	// check_status(philo);
	// while (philo->data->status == alive)
	// {
	// 	if (get_time_in_ms() - time_in_ms > philo->data->t_die - 1)
	// 		print_dead(philo);
	// 	if (get_time_in_ms() - time_in_ms >= time)
	// 		break ;
	// 	usleep(50);
	// }
}

void	log_status(t_philo *philo, char *str)
{
	long long	time_in_ms;

	pthread_mutex_lock(philo->table->logger_mutex);
	time_in_ms = get_time_in_ms() - philo->table->launch_time;
	printf("%lld %d %s\n", time_in_ms, philo->num, str);
	pthread_mutex_unlock(philo->table->logger_mutex);
}

void	print_dead(t_philo *philo)
{
	// long long	time_in_ms;
	printf("%d", philo->num);
	// pthread_mutex_lock(&philo->data->print);
	// time_in_ms = get_time_in_ms() - philo->data->t_launch;
	// if (philo->data->status == alive)
	// {
	// 	philo->data->status = dead;
	// 	usleep(1000);
	// 	printf("%lld %d died\n", time_in_ms, philo->id);
	// }
	// pthread_mutex_unlock(&philo->data->print);
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

void	print_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	for (i = 0; i < table->nb_philo; i++)
	{
		printf("[%d <- %d ->%d]\n", philos[i].left_fork, philos[i].num,
				philos[i].right_fork);
	}
}

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
