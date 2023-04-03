/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:05:03 by jnicolas          #+#    #+#             */
/*   Updated: 2023/03/16 16:18:32 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum
{
	EAT,
	SLEEP,
	THINK,
	DEAD
}					t_status;

typedef enum
{
	FREE,
	TAKEN
}					t_fork_status;

typedef struct
{
	int				nb_philo;
	int				todie_time;
	int				eat_time;
	int				sleep_time;
	int				number_of_eats;
	long long		launch_time;
	int				dinner_inprogress;
	pthread_mutex_t	*fork_mutex;
	t_fork_status	*fork_status;
	pthread_mutex_t	*logger_mutex;
	pthread_mutex_t	*global_mutex;
	pthread_mutex_t	*race_mutex;
	struct _philo	*philos;
}					t_table;

typedef struct _philo
{
	int				num;
	int				left_fork;
	int				right_fork;
	int				counter_of_eats;
	pthread_t		thread;
	t_status		status;
	long long		die_clock;
	long long		eat_clock;
	long long		sleep_clock;
	t_table			*table;
}					t_philo;

int					main(int argc, char **argv);
int					check_args(int argc, char **argv);
t_status			check_status(t_philo *philo);
void				print_philos(t_table *table);
void				print_forks(t_table *table);
void				start_state_observer(t_table *table);

void				*dinner(void *void_philo);
void				taking_fork(t_philo *philo);
void				eating(t_philo *philo, t_table *table);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				*is_dead(void *void_philo);
void				init_global_mutex(t_table *table);
void				init_logger(t_table *table);

t_table				*create_table(char **argv);
void				seat_philos(t_table *table);
void				put_forks(t_table *table);
void				start_dinner(t_table *table);
void				wait_dinner_end(t_table *table);
void				notify_right_fork_release(t_table *table, int num);
void				notify_left_fork_release(t_table *table, int num);

int					ft_atoi(const char *nptr);
long long			get_time_in_ms(void);
void				smart_sleep(long long time, t_philo *philo);
void				log_status(t_philo *philo, char *str);
void				print_dead(t_philo *philo);
int					round_left(int index, int n);
int					round_right(int index, int n);

int 				eatcount_constraint(t_philo *philo, t_table *table);
void				sleep_duration(long long duration);
void				write_status(int num_philo, t_status value, t_table *table);
t_status			read_status(int num_philo, t_table *table);
#endif