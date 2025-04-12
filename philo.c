/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:47:55 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/12 15:01:59 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	done_eating(t_table *table)
{
	int	i;
	int	n_philo;

	n_philo = 0;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->meal_mutex);
		if (table->philo[i].nbr_meals >= table->nbr_limit_meals)
			n_philo++;
		pthread_mutex_unlock(&table->meal_mutex);
		i++;
	}
	return (n_philo == table->philo_nbr);
}

static void	monitor(t_table *table)
{
	int		i;
	time_t	last_meal;

	while (1)
	{
		if (table->nbr_limit_meals && done_eating(table))
			return ;
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->meal_mutex);
			last_meal = table->philo[i].last_meal_time;
			pthread_mutex_unlock(&table->meal_mutex);
			if (get_time() >= last_meal + table->time_to_die)
			{
				print_action(&table->philo[i], "died");
				ft_usleep(500);
				return ;
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		t_table	table;

		parse_inpute(&table, av);
		data_init(&table);
		monitor(&table);
		destroy_mutex(&table);
	}
	else
		error_exit("./philo n_philo time_to_die time_to_eat time_to_sleep [n_meals].");
}
