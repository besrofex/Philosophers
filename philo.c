/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:47:55 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/13 12:09:40 by ylabser          ###   ########.fr       */
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

static void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->simulation_stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

static int	check_death(t_table *table, int i)
{
   time_t	current_time;

   current_time = get_time();
   pthread_mutex_lock(&table->meal_mutex);
   if (current_time >= table->philo[i].last_meal_time + table->time_to_die)
   {
      pthread_mutex_unlock(&table->meal_mutex);
      pthread_mutex_lock(&table->print_mutex);
      if (!table->simulation_stop)
      {
         printf("%ld %d died\n", current_time - table->start_dinner, table->philo[i].id);
         table->simulation_stop = 1;
      }
      pthread_mutex_unlock(&table->print_mutex);
      return (1);
   }
   pthread_mutex_unlock(&table->meal_mutex);
   return (0);
}

static void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		if (table->nbr_limit_meals && done_eating(table))
		{
			stop_simulation(table);
			return ;
		}
		i = 0;
		while (i < table->philo_nbr)
		{
			if (check_death(table, i))
			{
				ft_usleep(10);
				return ;
			}
			i++;
		}
		usleep(1000);
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
