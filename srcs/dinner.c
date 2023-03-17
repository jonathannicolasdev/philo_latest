/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:36:36 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/16 16:19:38 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_fork(t_philo *philo)
{
	printf("%d", philo->num);
	// pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	// print_status(philo, "has taken a fork");
	// if (philo->id == philo->data->philo_num)
	// 	pthread_mutex_lock(&philo->data->fork[0]);
	// else
	// 	pthread_mutex_lock(&philo->data->fork[philo->id]);
	// print_status(philo, "has taken a fork");
	// update_list(philo->data, philo->id);
}

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
	log_status(philo, "Thinking");
}

void	eating(t_philo *philo)
{
	int		nb_philo;
	int		num;
	int		forks_unavailable;
	t_table	*table;
	int		left2;
	int		right2;

	nb_philo = philo->table->nb_philo;
	num = philo->num;
	table = philo->table;
	forks_unavailable = 0;
	pthread_mutex_lock(philo->table->global_mutex);
	if (table->fork_status[philo->left_fork] == FREE
		&& table->fork_status[philo->right_fork] == FREE)
	{
		table->fork_status[philo->left_fork] = TAKEN;
		table->fork_status[philo->right_fork] = TAKEN;
	}
	else
		forks_unavailable = 1;
	pthread_mutex_unlock(table->global_mutex);
	if (forks_unavailable)
	{
		//log_status(philo,"Waiying forks");
		pthread_mutex_lock(&(table->fork_mutex[num]));
	}
	print_forks(table);
	// start eating
	philo->status = EAT;
	log_status(philo, "Eating");
	philo->eat_clock = get_time_in_ms();
	usleep(table->eat_time);
	log_status(philo, "Finished Eating");
	// leave forks
	pthread_mutex_lock(table->global_mutex);
	philo->status = SLEEP;
	table->fork_status[philo->left_fork] = FREE;
	table->fork_status[philo->right_fork] = FREE;
	log_status(philo, "Sleeping");
	left2 = round_left(philo->left_fork, nb_philo);
	right2 = round_right(philo->right_fork, nb_philo);
	if (table->fork_status[right2] == FREE
		&& table->philos[philo->right_fork].status == THINK)
	{
		table->fork_status[philo->right_fork] = TAKEN;
		table->fork_status[right2] = TAKEN;
		pthread_mutex_unlock(&(table->fork_mutex[philo->right_fork]));
	}
	if (table->fork_status[left2] == FREE
		&& table->philos[philo->left_fork].status == THINK)
	{
		table->fork_status[philo->left_fork] = TAKEN;
		table->fork_status[left2] = TAKEN;
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
	t_table *table;

	philo = void_philo;
	table = philo->table;
	// pthread_create(&th, NULL, &is_dead, philo);
	// pthread_detach(th);
	// Think,Eat, Sleep
	printf("[%d <- %d ->%d]\n", philo->left_fork, philo->num,
				philo->right_fork);
	printf("is all safe value %d \n", table->is_all_safe);
	while (table->is_all_safe)
	{
		thinking(philo);
		//eating(philo);
		//sleeping(philo);
	}
	return (0);
}
