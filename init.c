/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:17:48 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/28 18:13:15 by ylabser          ###   ########.fr       */
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

static void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2);
	while (!should_stop(philo))
	{
		take_forks(philo);
		update_meal_time(philo);
		print_action(philo, "is eating");
		update_meal_time(philo);
		ft_usleep(philo->table->time_to_eat);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
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
		pthread_mutex_lock(&table->meal_mutex);
		philo->nbr_meals = 0;
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&table->meal_mutex);
		philo->table = table;
		if (pthread_create(&philo->pthreads_id, NULL, routine, philo))
			error_exit("Error creating philosopher thread.");
		if (pthread_detach(table->philo[i].pthreads_id))
			error_exit("Failed to detach philosopher thread");
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

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
			error_exit("Error initializing fork mutex.");
		i++;
	}
	creat_philo(table);
}
