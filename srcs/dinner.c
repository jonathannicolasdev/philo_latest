/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:36:36 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/22 16:02:00 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (1)
		check_status(philo);
}

void	thinking(t_philo *philo)
{
	philo->status = THINK;
	log_status(philo, "is thinking");
}

void	eating(t_philo *philo)
{
	int		nb_philo;
	int		num;
	int		forks_assigned;
	t_table	*table;
	int		left2;
	int		right2;

	nb_philo = philo->table->nb_philo;
	num = philo->num;
	table = philo->table;
	forks_assigned = 0;
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
		forks_assigned = 1;
	pthread_mutex_unlock(table->global_mutex);
	if (forks_assigned)
	{
		pthread_mutex_lock(&(table->fork_mutex[num]));
	}
	philo->status = EAT;
	log_status(philo, "Eating");
	philo->eat_clock = get_time_in_ms();
	usleep(table->eat_time);
	log_status(philo, "Finished Eating");
	pthread_mutex_lock(table->global_mutex);
	philo->status = SLEEP;
	table->fork_status[philo->left_fork] = FREE;
	table->fork_status[philo->right_fork] = FREE;
	left2 = round_left(philo->left_fork, nb_philo);
	right2 = round_right(philo->right_fork, nb_philo);
	if (table->fork_status[right2] == FREE
		&& table->philos[philo->right_fork].status == THINK)
	{
		table->fork_status[philo->right_fork] = TAKEN;
		log_status(&table->philos[philo->right_fork], "Has taken a fork");
		table->fork_status[right2] = TAKEN;
		log_status(&table->philos[philo->right_fork], "Has taken a fork");
		pthread_mutex_unlock(&(table->fork_mutex[philo->right_fork]));
	}
	if (table->fork_status[left2] == FREE
		&& table->philos[philo->left_fork].status == THINK)
	{
		table->fork_status[philo->left_fork] = TAKEN;
		log_status(&table->philos[philo->left_fork], "Has taken a fork");
		table->fork_status[left2] = TAKEN;
		log_status(&table->philos[philo->left_fork], "Has taken a fork");
		pthread_mutex_unlock(&(table->fork_mutex[philo->left_fork]));
	}
	pthread_mutex_unlock(table->global_mutex);
}

void	sleeping(t_philo *philo)
{
	usleep(philo->table->sleep_time);
}

void	*dinner(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	table = philo->table;
	while (table->is_all_safe)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (0);
}
