/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnicolas <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:05:03 by jnicolas          #+#    #+#             */
/*   Updated: 2023/04/07 18:43:59 by jnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	DEAD
}					t_status;

typedef enum e_fork_status
{
	FREE,
	TAKEN
}					t_fork_status;

typedef struct s_table
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
	pthread_mutex_t	*eat_mutex;
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

//main.c
int					main(int argc, char **argv);
int					check_args(int argc, char **argv);
//init.c
void				init_logger(t_table *table);
void				init_global_mutex(t_table *table);
void				init_race_mutex(t_table *table);
void				init_eat_mutex(t_table *table);
void				seat_philos(t_table *table);
void				put_forks(t_table *table);
t_table				*create_table(char **argv);
//start.c
void				start_dinner(t_table *table);
void				wait_dinner_end(t_table *table);
//dinner.c
int					forks_taken(t_philo *philo, t_table *table);
void				notify_right_fork_release(t_table *table, int num);
void				notify_left_fork_release(t_table *table, int num);
void				eating(t_philo *philo, t_table *table);
void				*dinner(void *void_philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
//stateobserver.c
void				unlock_all_forks(t_table *table);
int					eatcount_constraint(t_philo *philo, t_table *table);
void				start_state_observer(t_table *table);
//utils.c
int					ft_atoi(const char *nptr);
int					round_left(int index, int n);
int					round_right(int index, int n);
void				write_status(int num_philo, t_status value, t_table *table);
t_status			read_status(int num_philo, t_table *table);
void				write_fork_status(int fork_id, t_fork_status value, t_table *table);
t_fork_status		read_fork_status(int fork_id, t_table *table);
void				write_dinner_inprogress(int value, t_table *table);
int					read_dinner_inprogress(t_table *table);

void				write_eat_clock(int num_philo, \
					long long value, t_table *table);
long long			read_eat_clock(int num_philo, t_table *table);
long long			get_time_in_ms(void);
void				sleep_duration(long long duration);
void				log_status(t_philo *philo, char *str);

void				print_philos(t_table *table);
void				print_forks(t_table *table);
void				free_all(t_table *table);
#endif
