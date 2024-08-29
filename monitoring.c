/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:07:58 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 15:00:22 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static void    kill_everyone(t_omni *data)
{
    int i;

    i = -1;
	while (++i < data->forum->philo_num)
	{
		pthread_mutex_lock(data->sophies[i]->state);
		data->sophies[i]->dead = 1;
		pthread_mutex_unlock(data->sophies[i]->state);
    }
}

static int	who_died(t_omni *data)
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

static int	who_ate(t_omni *data)
{
	int	i;

	i = -1;
	while (++i < data->forum->philo_num)
	{
		pthread_mutex_lock(data->sophies[i]->meal_lock);
		if (data->sophies[i]->cur_meal == data->forum->meal_num)
		{
			pthread_mutex_lock(data->sophies[i]->state);
			data->sophies[i]->dead = 1;
			pthread_mutex_unlock(data->sophies[i]->state);
			pthread_mutex_unlock(data->sophies[i]->meal_lock);
			kill_everyone(data);
			return (1);
		}
	}
	pthread_mutex_unlock(data->sophies[i]->meal_lock);
	return (0);
}

void	*monitoring(void *arg)
{
    t_omni  *data;

    data = (t_omni *)arg;
	while (1)
	{
		if (who_died(data))
			break ;
		if (who_ate(data));
			break ;
	}
}
