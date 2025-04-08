/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:18:42 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/08 13:34:13 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Malloc Error.");
	return (ret);
}

long	get_time(void)
{
	struct timeval	tv;
	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed.");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
