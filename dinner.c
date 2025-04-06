/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:22:03 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/06 22:47:24 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_simmulation(void *arg)
{}

static void	one_philo(t_table *table)
{}

void	dinner_start(t_table	*table)
{
	int	i;

	i = 0;
	if (table->forks == 0)
		return ;
	else if (table->philo_nbr == 1)
		one_philo(table);
	else
	{
		while (i < table->philo_nbr)
		{
			if (pthread_create(&table->philo[i].pthreads_id , NULL, (void *)dinner_simmulation, &table->philo[i]))
				error_exit("Error Creat thread.");
			i++;
		}
	}
}