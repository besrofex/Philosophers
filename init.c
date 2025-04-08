/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:17:48 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/07 17:48:33 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_fork *fork, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->left_fork = &fork[i];
	philo->right_fork = &fork[(i + 1) % philo_nbr];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &fork[i];
		philo->left_fork = &fork[(i + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->nbr_meals = 0;
		philo->full = false;
		philo->table = table;
		assign_fork(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;
	
	i = 0;
	table->threads_ready = false;
	table->someone_died = 0;
	table->philo = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL)) // check this (condition if) ??????
			error_exit("Error Mutex init.");
		table->forks[i].id = i;
		i++;
	}
	philo_init(table);
}
