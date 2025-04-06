/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:47:55 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/06 19:17:01 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		t_table	table;
		
		parse_inpute(&table, av);
		data_init(&table);
	}
	else
		error_exit("Wrong input.");
}