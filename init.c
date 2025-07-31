/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:17:48 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/29 19:24:43 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->stop_mutex);
	if (!table->simulation_stop)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("%ld %d %s\n", get_time()
			- table->start_dinner, philo->id, action);
		pthread_mutex_unlock(&table->print_mutex);
	}
	pthread_mutex_unlock(&philo->table->stop_mutex);
}

static void	creat_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->start_dinner = get_time();
	table->simulation_stop = 0;
	while (i < table->philo_nbr)
	{
		philo = &table->philo[i];
		philo->id = i + 1;
		philo->right = i;
		philo->left = (i + 1) % table->philo_nbr;
		philo->nbr_meals = 0;
		philo->last_meal_time = get_time();
		philo->table = table;
		if (pthread_create(&philo->pthreads_id, NULL, routine, philo))
			error_exit("Error creating philosopher thread.");
		i++;
	}
}

static void	ft_destroy_init(t_table *table)
{
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	error_exit("Error initializing fork mutex.");
}

void	data_init(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	if (pthread_mutex_init(&table->print_mutex, NULL))
		error_exit("Failed to init print mutex.");
	if (pthread_mutex_init(&table->meal_mutex, NULL))
		error_exit("Failed to init meal mutex.");
	if (pthread_mutex_init(&table->stop_mutex, NULL))
		error_exit("Failed to init stop mutex.");
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL))
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&table->fork_mutex[j]);
				j++;
			}
			ft_destroy_init(table);
		}
		i++;
	}
	creat_philo(table);
}
