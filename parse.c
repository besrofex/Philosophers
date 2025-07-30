/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:19:53 by ylabser           #+#    #+#             */
/*   Updated: 2025/07/29 20:18:33 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static char	*valid_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		error_exit("Only positive nbr.");
	if (!is_digit(str[i]))
		error_exit("The input is not a correct digit.");
	return (&str[i]);
}

static long	ft_atol(char *str)
{
	long	nbr;
	int		i;

	i = 0;
	nbr = 0;
	str = valid_input(str);
	while (str[i])
	{
		if (!is_digit(str[i]))
			error_exit("The input is not a digit.");
		if (nbr > INT_MAX)
         error_exit("The value is too big.");
		nbr = nbr * 10 + (str[i++] - '0');
	}
	if (nbr > INT_MAX)
		error_exit("The value is too big.");
	return (nbr);
}

void	parse_inpute(t_table *table, char **args)
{
	long	meals;

	if (ft_atol(args[1]) < 1 || ft_atol(args[1]) > MAX_PHILOS)
		error_exit("Invalid number of philosophers (out of allowed range).");
	table->philo_nbr = ft_atol(args[1]);
	if (ft_atol(args[2]) < MIN_TIME)
		error_exit("Time to die too short (below minimum allowed).");
	table->time_to_die = ft_atol(args[2]);
	if (ft_atol(args[3]) < MIN_TIME)
		error_exit("Time to eat too short (below minimum allowed).");
	table->time_to_eat = ft_atol(args[3]);
	if (ft_atol(args[4]) < MIN_TIME)
		error_exit("Time to sleep too short (below minimum allowed).");
	table->time_to_sleep = ft_atol(args[4]);
	if (args[5])
	{
		meals = ft_atol(args[5]);
		if (meals <= 0)
			error_exit("Number of meals must be positive value.");
		table->nbr_limit_meals = meals;
	}
	else
		table->nbr_limit_meals = 0;
}
