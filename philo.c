/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:47:55 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/29 21:24:40 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	done_eating(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->meal_mutex);
	while (i < table->philo_nbr)
	{
		if (table->philo[i].nbr_meals < table->nbr_limit_meals)
		{
			pthread_mutex_unlock(&table->meal_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_mutex);
	return (1);
}

static void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->simulation_stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

static int	check_death(t_table *table, int i)
{
	time_t	last_meal;
	time_t	current_time;
	int		died;

	pthread_mutex_lock(&table->meal_mutex);
	last_meal = table->philo[i].last_meal_time;
	current_time = get_time();
	died = (current_time - last_meal >= table->time_to_die);
	pthread_mutex_unlock(&table->meal_mutex);
	if (died)
	{
		pthread_mutex_lock(&table->stop_mutex);
		if (!table->simulation_stop)
		{
			pthread_mutex_lock(&table->print_mutex);
			printf("%ld %d died\n", current_time
				- table->start_dinner, table->philo[i].id);
			pthread_mutex_unlock(&table->print_mutex);
			table->simulation_stop = 1;
		}
		pthread_mutex_unlock(&table->stop_mutex);
		return (1);
	}
	return (0);
}

static void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		usleep(50);
		if (table->nbr_limit_meals && done_eating(table))
		{
			stop_simulation(table);
			ft_usleep(10, table);
			return ;
		}
		i = 0;
		while (i < table->philo_nbr)
		{
			if (check_death(table, i))
			{
				ft_usleep(10, table);
				return ;
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_inpute(&table, av);
		data_init(&table);
		monitor(&table);
		destroy_mutex(&table);
	}
	else
		error_exit("Wrong input.");
	return (0);
}
