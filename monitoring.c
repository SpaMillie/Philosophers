/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:07:58 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 13:13:02 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

int	who_died(t_omni *data)
{
	int	i;

	i = -1;
	while (++i < data->forum->philo_num)
	{
		pthread_mutex_lock(data->sophies[i]->state);
		if (get_time() - data->forum->start_time > data->forum->time_to_die)
		{
			print_out("has died", data->sophies[i]);
			data->sophies[i]->dead = 1;
			pthread_mutex_unlock(data->sophies[i]->state);
			kill_everyone(data);
			return (1);
		}
	}
	pthread_mutex_unlock(data->sophies[i]->state);
	return (0);
}

int	who_ate(t_omni *data)
{
	int	i;

	i = -1;
	while (++i < data->forum->philo_num)
	{
		pthread_mutex_lock(data->sophies[i]->meal_lock);
		if (get_time() - data->forum->start_time > data->forum->time_to_die)
		{
			data->sophies[i]->dead = 1;
			pthread_mutex_unlock(data->sophies[i]->meal_lock);
			kill_everyone(data);
			return (1);
		}
	}
	pthread_mutex_unlock(data->sophies[i]->meal_lock);
	return (0);
}

void	monitoring(t_omni *data)
{
	while (1)
	{
		if (who_died(data))
			break ;
		if (who_ate(data));
			break ;
	}

	//unlock everything, change flags, destroy mutexes 
	// check = -1;
	// while (++check < data->forum->philo_num)
	// 	pthread_join(data->sophies[check], NULL);
}
