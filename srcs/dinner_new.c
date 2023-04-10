/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:36:36 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/07 16:09:21 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_forks(t_philo *philo, t_table *table)
{
	if (table->dinner_inprogress == 0)
		return (0);
	pthread_mutex_lock(table->global_mutex);
	if (table->fork_status[philo->left_fork] == FREE && table->fork_status[philo->right_fork] == FREE)
	{
		pthread_mutex_lock(&table->fork_mutex[philo->left_fork]);
		log_status(philo, "has taken a fork");
		table->fork_status[philo->left_fork] = TAKEN;
		pthread_mutex_lock(&table->fork_mutex[philo->right_fork]);
		log_status(philo, "has taken a fork");
		table->fork_status[philo->right_fork] = TAKEN;
        philo->eat_clock = get_time_in_ms();
        log_status(philo, "is eating");
        pthread_mutex_unlock(table->global_mutex);
        sleep_duration(table->eat_time);
		table->fork_status[philo->left_fork] = FREE;
		table->fork_status[philo->right_fork] = FREE;
		pthread_mutex_unlock(&table->fork_mutex[philo->left_fork]);
		pthread_mutex_unlock(&table->fork_mutex[philo->right_fork]);
        philo->counter_of_eats++;
		return (0);
	}
	pthread_mutex_unlock(table->global_mutex);
	return (1);
}

void	go_to_sleep(t_philo *philo, t_table *table)
{
    log_status(philo, "is sleeping");
    sleep_duration(table->sleep_time);
}

void	start_to_think(t_philo *philo, t_table *table)
{
    (void)table;
    log_status(philo, "is thinking");
}

void    *dinner(void *void_philo)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)void_philo;
    table = philo->table;
    if (philo->num % 2  == 1)
    {
        usleep(1000);
    }
    if (table->nb_philo == 1)
	{
		pthread_mutex_lock(&table->fork_mutex[0]);
		log_status(philo, "has taken a fork");
		sleep_duration(table->todie_time);
		pthread_mutex_unlock(&table->fork_mutex[0]);
		return (0);
	}
    while (table->dinner_inprogress)
    {
        while (grab_forks(philo, table))
            usleep(100);
        go_to_sleep(philo, table);
        start_to_think(philo, table);
        usleep(500);
    }
    return (0);    
} 