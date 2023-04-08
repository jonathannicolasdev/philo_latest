/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:36:36 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/07 15:59:22 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_taken(t_philo *philo, t_table *table)
{
	int	is_forks_assigned;

	is_forks_assigned = 0;
	pthread_mutex_lock(philo->table->global_mutex);
	if (table->fork_status[philo->left_fork] == FREE
		&& table->fork_status[philo->right_fork] == FREE)
	{
		table->fork_status[philo->left_fork] = TAKEN;
		log_status(philo, "Has taken a fork");
		if (philo->right_fork == philo->left_fork)
			is_forks_assigned = 1;
		else
		{
			table->fork_status[philo->right_fork] = TAKEN;
			log_status(philo, "Has taken a fork");
		}
	}
	else
		is_forks_assigned = 1;
	pthread_mutex_unlock(table->global_mutex);
	return (is_forks_assigned);
}

void	notify_right_fork_release(t_table *table, int num)
{
	int		right2;
	t_philo	*philo;

	philo = &table->philos[num];
	right2 = round_right(philo->right_fork, philo->table->nb_philo);
	if (table->fork_status[right2] == FREE
		&& read_status(philo->right_fork, table) == THINK)
	{
		if (read_status(right2, table) != THINK || \
			read_eat_clock(right2, table) >= \
			read_eat_clock(philo->right_fork, table))
		{
			table->fork_status[philo->right_fork] = TAKEN;
			log_status(&table->philos[philo->right_fork], "Has taken a fork");
			table->fork_status[right2] = TAKEN;
			log_status(&table->philos[philo->right_fork], "Has taken a fork");
			pthread_mutex_unlock(&(table->fork_mutex[philo->right_fork]));
		}
	}
}

void	notify_left_fork_release(t_table *table, int num)
{
	int		left2;
	int		left3;
	t_philo	*philo;

	philo = &table->philos[num];
	left2 = round_left(philo->left_fork, philo->table->nb_philo);
	left3 = round_left(left2, philo->table->nb_philo);
	if (table->fork_status[left2] == FREE
		&& read_status(left2, table) == THINK)
	{
		if (read_status(left3, table) != THINK || \
			read_eat_clock(left3, table) >= read_eat_clock(left2, table))
		{
			table->fork_status[philo->left_fork] = TAKEN;
			log_status(&table->philos[left2], "Has taken a fork");
			table->fork_status[left2] = TAKEN;
			log_status(&table->philos[left2], "Has taken a fork");
			pthread_mutex_unlock(&(table->fork_mutex[left2]));
		}
	}
}

void	eating(t_philo *philo, t_table *table)
{
	if (forks_taken(philo, table))
	{
		pthread_mutex_lock(&(table->fork_mutex[philo->num]));
	}
	pthread_mutex_lock(table->race_mutex);
	philo->status = EAT;
	philo->eat_clock = get_time_in_ms();
	philo->counter_of_eats++;
	pthread_mutex_unlock(table->race_mutex);
	log_status(philo, "is eating");
	sleep_duration(table->eat_time);
	pthread_mutex_lock(table->global_mutex);
	philo->status = SLEEP;
	log_status(philo, "is sleeping");
	table->fork_status[philo->left_fork] = FREE;
	table->fork_status[philo->right_fork] = FREE;
	notify_right_fork_release(table, philo->num);
	notify_left_fork_release(table, philo->num);
	pthread_mutex_unlock(table->global_mutex);
}

void	*dinner(void *void_philo)
{
	t_philo	*philo;
	t_table	*table;

	philo = void_philo;
	table = philo->table;
	write_eat_clock(philo->num, get_time_in_ms(), table);
	while (read_dinner_inprogress(table) \
		&& !eatcount_constraint(philo, table))
	{
		eating(philo, table);
		if (read_dinner_inprogress(table) && !eatcount_constraint(philo, table))
			sleeping(philo);
		if (read_dinner_inprogress(table) && !eatcount_constraint(philo, table))
			thinking(philo);
		usleep(50);
	}
	return (0);
}
