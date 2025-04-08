/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:22:03 by ylabser           #+#    #+#             */
/*   Updated: 2025/04/08 13:33:50 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int has_died(t_table *table)
{
    int result;

    pthread_mutex_lock(&table->death_mutex);
    result = table->someone_died;
    pthread_mutex_unlock(&table->death_mutex);
    return (result);
}

static void smart_sleep(int duration, t_table *table)
{
    long start;

    start = get_time();
    while (!has_died(table))
    {
        if ((int)(get_time() - start) >= duration)
            break;
        usleep(100);
    }
}

static void print_action(t_philo *philo, char *action)
{
    long timestamp;

    pthread_mutex_lock(&philo->table->print_mutex); 
    if (!has_died(philo->table))
    {
        timestamp = get_time() - philo->table->start_dinner;
        printf("%ld %d %s\n", timestamp, philo->id, action);
    }
    pthread_mutex_unlock(&philo->table->print_mutex);
}

static void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->left_fork->fork);
        print_action(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->right_fork->fork);
        print_action(philo, "has taken a fork");
    }
}

static void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

static void eat(t_philo *philo)
{
   take_forks(philo);
   pthread_mutex_lock(&philo->table->meal_mutex);
   philo->last_meal_time = get_time();
   pthread_mutex_unlock(&philo->table->meal_mutex);
   print_action(philo, "is eating");
   smart_sleep(philo->table->time_to_eat, philo->table); 
   philo->nbr_meals++;
   if (philo->nbr_meals >= philo->table->nbr_limit_meals && philo->table->nbr_limit_meals > 0)
      philo->full = true;  
   drop_forks(philo);
	print_action(philo, "is sleeping");
   smart_sleep(philo->table->time_to_sleep, philo->table);
}

static void *monitor_routine(void *data)
{
    t_table *table;
    int i;
    long current_time;
    int full_count;

   table = (t_table *)data;
   usleep(1000);
   while (1)
   {
      i = -1;
      full_count = 0;
      while (++i < table->philo_nbr)
      {
         pthread_mutex_lock(&table->meal_mutex);
         current_time = get_time();
         if (current_time - table->philo[i].last_meal_time > table->time_to_die)
         {
            print_action(&table->philo[i], "died");
            pthread_mutex_lock(&table->death_mutex);
            table->someone_died = 1;
            pthread_mutex_unlock(&table->death_mutex);
            pthread_mutex_unlock(&table->meal_mutex);
            return (NULL);
         }
         if (table->philo[i].full)
            full_count++;  
         pthread_mutex_unlock(&table->meal_mutex);
      }
      if (full_count == table->philo_nbr && table->nbr_limit_meals > 0)
      {
         pthread_mutex_lock(&table->death_mutex);
         table->someone_died = 1;
         pthread_mutex_unlock(&table->death_mutex);
         return (NULL);
      }
      usleep(1000);
      if (has_died(table))
         return (NULL);
   }
   return (NULL);
}

static void *dinner_simulation(void *data)
{
   t_philo *philo;

   philo = (t_philo *)data;
   while (!philo->table->threads_ready)
      usleep(50);
    if (philo->id % 2 == 0)
        usleep(philo->table->time_to_eat / 2);
    while (!has_died(philo->table))
    {
      if (philo->full)
         break;
      eat(philo);
      print_action(philo, "is thinking");
      usleep(100);
    }
    return (NULL);
}

static void one_philo(t_table *table)
{
	printf("%ld 1 has taken a fork\n", 0L);
	usleep(table->time_to_die);
   pthread_mutex_lock(&table->death_mutex);
   table->someone_died = 1;
	printf("%ld 1 died\n", table->time_to_die / 1000);
   pthread_mutex_unlock(&table->death_mutex);
   pthread_mutex_unlock(&table->meal_mutex);
}

void dinner_start(t_table *table)
{
    int i;
    pthread_t monitor_id;

   if (table->nbr_limit_meals == 0) 
      return;   
   if (table->philo_nbr == 1)
   {
      one_philo(table);
      return;
   }
	table->start_dinner = get_time();
   i = -1;
   while (++i < table->philo_nbr)
   {
      if (pthread_create(&table->philo[i].pthreads_id, NULL,
                           &dinner_simulation, &table->philo[i]))
         error_exit("Error creating thread.");
      usleep(50);
   }
   table->start_dinner = get_time();
   table->threads_ready = true;
   if (pthread_create(&monitor_id, NULL, &monitor_routine, table))
      error_exit("Error creating monitor thread.");
    i = -1;
   while (++i < table->philo_nbr)
   {
      if (pthread_join(table->philo[i].pthreads_id, NULL))
         error_exit("Error joining threads.");
   }
   if (pthread_join(monitor_id, NULL))
      error_exit("Error joining monitor thread.");
}
