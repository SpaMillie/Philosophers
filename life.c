/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:00:59 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 11:46:55 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"
int	assassin(t_philo *sopher)
{
	pthread_mutex_lock(&sopher->state);
	print_out("has died", sopher);
	change_stop(sopher);
	sopher->dead = 1;
	pthread_mutex_unlock(&sopher->state);	
	return (1);
}

static int	table_4_1(t_philo *sopher)
{
    pthread_mutex_lock(sopher->left_fork);
	print_out("has taken a fork", sopher); 
	ft_usleep(sopher->time_to_die, sopher->start_time);
	assassin(sopher);
	return (1);
}

static int	eating(t_philo  *sopher)
{
	if (sopher->philo_num == 1)
		return (table_4_1(sopher));
    pthread_mutex_lock(sopher->left_fork);
	print_out("has taken a fork", sopher);
	pthread_mutex_lock(sopher->right_fork);
	print_out("has taken a fork", sopher);
	pthread_mutex_lock(&sopher->meal_lock);
 	if (!check_state(sopher))
	{
		if (get_time() - sopher->last_ate > sopher->time_to_die)
			return (assassin(sopher));
		else
		{
			sopher->last_ate = print_out("is eating", sopher);
			if (sopher->time_to_die < sopher->time_to_eat)
				return (sudden_death(sopher, 1));
			ft_usleep(sopher->time_to_eat, sopher->last_ate);
		}
	}
	sopher->cur_meal++;
	pthread_mutex_unlock(&sopher->meal_lock); 
   	pthread_mutex_unlock(sopher->right_fork); 
   	pthread_mutex_unlock(sopher->left_fork);
	return (0);
}

static int	sleeping(t_philo *sopher)
{
	if (!check_state(sopher))
    {
		print_out("is sleeping", sopher);
		if (get_time() - sopher->last_ate > sopher->time_to_die)
            return (assassin(sopher));
        else
		{
			if (sopher->time_to_die < sopher->time_to_sleep)
				return (sudden_death(sopher, 0));
			ft_usleep(sopher->time_to_sleep, sopher->last_ate + sopher->time_to_eat); 
		}
    }
	if (get_time() - sopher->last_ate > sopher->time_to_die)
		return (assassin(sopher));
	return (0);
}

static void	thinking(t_philo *sopher)
{
	print_out("is thinking", sopher);
	if ((sopher->id == 0 || \
		sopher->id % 2 == 0) && sopher->cur_meal == 0)
		ft_usleep(sopher->time_to_die / 10, sopher->start_time);
}

static void	*life(void *arg)
{
    t_philo *sopher;

    sopher = (t_philo *)arg;
	// print_out("has been born", sopher->timing, sopher->id, sopher->start_time);
	// ft_usleep(10, get_time());
	pthread_mutex_lock(sopher->start);
	// print_out("philo locked the start", sopher->timing, sopher->id, sopher->start_time);
	pthread_mutex_unlock(sopher->start);
	// print_out("philo unlocked the start", sopher->timing, sopher->id, sopher->start_time);
	// printf("%d\n", check_state(sopher));
	while(1)
	{
		// printf("life started\n");
		if (check_state(sopher))
		{
			// printf("exited 1\n");
			break ;
		}
		thinking(sopher);
		if (check_state(sopher))
		{
			// printf("exited 2\n");
			break ;
		}
		if (eating(sopher) == 0)
			sleeping(sopher);
	}
}

int	philogenesis(t_omni *data)
{
	int	i;

	i = 0;
	// printf("entered philogenesis\n");
	// pthread_mutex_lock(&data->tor->start);
	// printf("start locked by philogenesis\n");
	data->tor->start_time = lock_time(&data->tor->timing); 
	// printf("good philogenesis\n");
	while (i < data->tor->philo_num)
	{
		data->sophies[i].start_time = data->tor->start_time;
		data->sophies[i].last_ate = data->sophies[i].start_time;
        // printf("philo is %d and start time is %lu\n", data->sophies[i].id, data->sophies[i].start_time);
		if (pthread_create(&(data->sophies[i].thread), NULL, \
			&life, (void *)&data->sophies[i]) != 0)
		{
			printf("Error: philogenesis failed\n");
			while (--i > -1)
				pthread_join(data->sophies[i].thread, NULL);
            // data->can_go = 1;
			// pthread_mutex_unlock(&data->tor->start);
			return (1);
		}
		i++;
	}
    // printf("every thread created\n");
    // // data->can_go = 1;
	// printf("data is now %d\n", data->can_go);
	// pthread_mutex_unlock(&data->tor->start);
	// printf("start unlocked\n");
	return (0);
}
