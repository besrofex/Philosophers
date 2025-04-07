/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:46:26 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/07 16:39:18 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_fork t_fork;
typedef struct s_philo t_philo;
typedef struct s_table t_table;

struct s_fork
{
	pthread_mutex_t	fork;
	int					id;
};

struct s_philo
{
	int        id;
	long        nbr_meals;
	long        last_meal_time;
	bool        full;
	t_fork      *left_fork;
	t_fork		*right_fork;
	t_table		*table;
	pthread_t	pthreads_id;
};

struct s_table
{
	long        philo_nbr;
	long        time_to_die;
	long        time_to_eat;
	long        time_to_sleep;
	long        nbr_limit_meals;
	long			start_dinner;
	bool			threads_ready;
	int				someone_died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo    *philo;
	t_fork     *forks;
};

// main
int	main(int ac, char **av);

// utils
void	error_exit(char *str);
void	*safe_malloc(size_t byte);
long	get_time(void); 

// init
void	data_init(t_table *table);

// parsing
void	parse_inpute(t_table *table, char **args);

// dinner
void	dinner_start(t_table	*table);

#endif