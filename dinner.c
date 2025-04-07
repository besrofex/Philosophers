/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:22:03 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/07 16:40:42 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_died(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->death_mutex);
	result = table->someone_died;
	pthread_mutex_unlock(&table->death_mutex);
	return (result);
}

static void	smart_sleep(int duration, t_table *table)
{
	long	start;

	start = get_time();
	while (!has_died(table))
	{
		if ((int)(get_time() - start) >= duration)
			break ;
		usleep(100); // petite pause pour éviter de surcharger le CPU
	}
}

static void	*dinner_simmulation(void *data)
{
	t_philo	*philo = (t_philo *)data;

	while (!philo->table->threads_ready)
		;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (!has_died(philo->table)) // une fonction que tu dois faire
	{
		take_forks(philo);
		print_action(philo, "is eating");
		philo->last_meal_time = get_time();
		smart_sleep(philo->table->time_to_eat, philo->table);
		philo->nbr_meals++;
		drop_forks(philo);

		if (philo->table->nbr_limit_meals != -1 && philo->nbr_meals >= philo->table->nbr_limit_meals)
			break ;

		print_action(philo, "is sleeping");
		smart_sleep(philo->table->time_to_sleep, philo->table);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
 

static void	one_philo(t_table *table)
{}

void	dinner_start(t_table *table)
{
	int	i = -1;

	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		one_philo(table);
		return ;
	}

	table->start_dinner = get_time();
	table->threads_ready = true;

	while (++i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i].pthreads_id, NULL,
				&dinner_simmulation, &table->philo[i]))
			error_exit("Error creating thread.");
	}

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_join(table->philo[i].pthreads_id, NULL))
			error_exit("Error joining threads.");
	}
}
