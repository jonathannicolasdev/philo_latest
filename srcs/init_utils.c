/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:37:00 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/02 20:41:30 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_logger(t_table *table)
{
	pthread_mutex_t	*loggermutex;

	loggermutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(loggermutex, NULL);
	table->logger_mutex = loggermutex;
}

void	init_global_mutex(t_table *table)
{
	pthread_mutex_t	*globalmutex;

	globalmutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(globalmutex, NULL);
	table->global_mutex = globalmutex;
}

void	init_race_mutex(t_table *table)
{
	pthread_mutex_t	*racemutex;

	racemutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(racemutex, NULL);
	table->race_mutex = racemutex;
}
