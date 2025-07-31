/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:18:42 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/29 21:25:56 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed.");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t time, t_table *table)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time)
	{
		pthread_mutex_lock(&table->stop_mutex);
		if (table->simulation_stop)
		{
			pthread_mutex_unlock(&table->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->stop_mutex);
		usleep(50);
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philo[i].pthreads_id, NULL);
		i++;
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
}
