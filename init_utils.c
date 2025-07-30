/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:05:42 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/28 17:49:51 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->left < philo->right)
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left]);
		print_action(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->left]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->right]);
}

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->table->stop_mutex);
	stop = philo->table->simulation_stop;
	pthread_mutex_unlock(&philo->table->stop_mutex);
	return (stop);
}

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
}
