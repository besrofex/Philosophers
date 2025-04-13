/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:46:26 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/13 12:17:26 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_philo
{
	int			id;
	int			left;
	int			right;
	long		nbr_meals;
	time_t		last_meal_time;
	t_table		*table;
	pthread_t	pthreads_id;
};

struct s_table
{
	long			philo_nbr;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			nbr_limit_meals;
	time_t			start_dinner;
	t_philo			philo[200];
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fork_mutex[200];
	pthread_mutex_t	meal_mutex;
};

// main
int		main(int ac, char **av);

// utils
void	error_exit(char *str);
time_t	get_time(void);
void	ft_usleep(time_t time);
void	destroy_mutex(t_table *table);

// init
void	data_init(t_table *table);
void	print_action(t_philo *philo, char *action);

// parsing
void	parse_inpute(t_table *table, char **args);

#endif