#include "philo.h"

long long	ft_get_time(void)
{
	long long		sec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (sec);
}

void	ft_wait(t_table *table, int time)
{
	long long now_time;
	long long start_time;

	start_time = ft_get_time();
	while (table->is_all_safe)
	{
		now_time = ft_get_time();
		if (now_time - start_time >= time)
			break ;
		usleep(300);
	}
}