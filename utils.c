/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:18:42 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/06 19:23:53 by ylabser          ###   ########.fr       */
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

	ret = nalloc(bytes);
	if (ret == NULL)
		error_exit("Malloc Error.");
	return (ret);
}