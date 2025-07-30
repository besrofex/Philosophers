/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:17:47 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/30 18:17:47 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*handle_single_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->fork_mutex[philo->left]);
	print_action(philo, "has taken a fork");
	ft_usleep(table->time_to_die);
	pthread_mutex_unlock(&table->fork_mutex[philo->left]);
	return (NULL);
}

static int	check_meal_limit(t_philo *philo)
{
	t_table	*table;
	int		should_break ;

	should_break = 0;
	table = philo->table;
	pthread_mutex_lock(&table->meal_mutex);
	if (table->nbr_limit_meals > 0
		&& philo->nbr_meals >= table->nbr_limit_meals)
		should_break = 1;
	pthread_mutex_unlock(&table->meal_mutex);
	return (should_break);
}

static void	philo_eat(t_philo *philo)
{
	print_action(philo, "is eating");
	update_meal_time(philo);
	ft_usleep(philo->table->time_to_eat);
}

static void	philo_sleep_and_think(t_philo *philo)
{
	if (should_stop(philo))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	if (should_stop(philo))
		return ;
	print_action(philo, "is thinking");
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (table->philo_nbr == 1)
		return (handle_single_philo(philo));
	if (philo->id % 2 == 0)
		ft_usleep(table->time_to_eat / 2);
	while (!should_stop(philo))
	{
		take_forks(philo);
		if (check_meal_limit(philo))
		{
			drop_forks(philo);
			break ;
		}
		philo_eat(philo);
		drop_forks(philo);
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
