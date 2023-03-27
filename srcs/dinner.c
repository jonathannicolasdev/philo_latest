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
	philo->status = THINK;
	log_status(philo, "is thinking");
}

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
		table->fork_status[philo->right_fork] = TAKEN;
		log_status(philo, "Has taken a fork");
	}
	else
		is_forks_assigned = 1;
	pthread_mutex_unlock(table->global_mutex);
	return (is_forks_assigned);
}

void	eating(t_philo *philo, t_table *table)
{
	int	left3;
	int	left2;
	int	right2;

	if (forks_taken(philo, table))
	{
		pthread_mutex_lock(&(table->fork_mutex[philo->num]));
	}
	philo->status = EAT;
	log_status(philo, "is eating");
	philo->eat_clock = get_time_in_ms();
	usleep(table->eat_time * 1000);
	pthread_mutex_lock(table->global_mutex);
	philo->status = SLEEP;
	table->fork_status[philo->left_fork] = FREE;
	table->fork_status[philo->right_fork] = FREE;
	left2 = round_left(philo->left_fork, philo->table->nb_philo);
	right2 = round_right(philo->right_fork, philo->table->nb_philo);
	if (table->fork_status[right2] == FREE
		&& table->philos[philo->right_fork].status == THINK)
	{
		if (table->philos[right2].status != THINK
			|| table->philos[right2].eat_clock >= \
			table->philos[philo->right_fork].eat_clock)
		{
			table->fork_status[philo->right_fork] = TAKEN;
			log_status(&table->philos[philo->right_fork], "Has taken a fork");
			table->fork_status[right2] = TAKEN;
			log_status(&table->philos[philo->right_fork], "Has taken a fork");
			pthread_mutex_unlock(&(table->fork_mutex[philo->right_fork]));
		}
	}
	if (table->fork_status[left2] == FREE
		&& table->philos[left2].status == THINK)
	{
		left3 = round_left(left2, philo->table->nb_philo);
		if (table->philos[left3].status != THINK
			|| table->philos[left3].eat_clock >= table->philos[left2].eat_clock)
		{
			table->fork_status[philo->left_fork] = TAKEN;
			log_status(&table->philos[left2], "Has taken a fork");
			table->fork_status[left2] = TAKEN;
			log_status(&table->philos[left2], "Has taken a fork");
			pthread_mutex_unlock(&(table->fork_mutex[left2]));
		}
	}
	pthread_mutex_unlock(table->global_mutex);
}

void	sleeping(t_philo *philo)
{
	log_status(philo, "is sleeping");
	usleep(philo->table->sleep_time * 1000);
}

void	*dinner(void *void_philo)
{
	t_philo	*philo;
	t_table	*table;

	philo = void_philo;
	table = philo->table;
	if (philo->num % 2 == 1)
		usleep(philo->table->eat_time);
	while (philo->table->dinner_inprogress)
	{
		thinking(philo);
		eating(philo, table);
		sleeping(philo);
	}
	return (0);
}
