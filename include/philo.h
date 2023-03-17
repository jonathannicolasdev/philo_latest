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
	int				must_eat_num;
	int				is_all_safe;
	long long		launch_time;
	pthread_mutex_t	*fork_mutex;
	t_fork_status	*fork_status;
	pthread_mutex_t	*logger_mutex;
	pthread_mutex_t	eat;
	pthread_mutex_t	*global_mutex;
	struct _philo	*philos;
}					t_table;

typedef struct _philo
{
	int				num;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_status		status;
	int				die_clock;
	int				eat_clock;
	int				sleep_clock;
	long long		last_eat_time;
	int				number_of_meals;
	t_table			*table;
}					t_philo;

int					main(int argc, char **argv);
int					check_args(int argc, char **argv);
t_status			check_status(t_philo *philo);
void				print_philos(t_table *table);
void				print_forks(t_table *table);

void				*dinner(void *void_philo);
void				taking_fork(t_philo *philo);
void				eating(t_philo *philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				*is_dead(void *void_philo);
void				init_global_mutex(t_table *table);
void				init_logger(t_table *table);

t_table				*create_table(int argc, char **argv);
void				seat_philos(t_table *table);
void				put_forks(t_table *table);
//void				start_dinner(t_table *table);
void				wait_dinner_end(t_table *table);

int					ft_atoi(const char *nptr);
long long			get_time_in_ms(void);
void				smart_sleep(long long time, t_philo *philo);
void				log_status(t_philo *philo, char *str);
void				print_dead(t_philo *philo);
int					round_left(int index, int n);
int					round_right(int index, int n);


long long			ft_get_time(void);
void				ft_wait(t_table *table, int time);
int					ft_start_philo(t_table *table, t_philo *philo);
void				ft_check_die(t_table *table);
int					check_eat_time(t_table *table);
int					check_eat_num(t_table *table);
int					start_dinner(t_table *table);

#endif
