/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:07:58 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/31 11:54:27 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static void    kill_everyone(t_omni *data)
{
    int i;

    i = 0;
	while (i < data->tor->philo_num)
	{
		pthread_mutex_lock(&data->sophies[i].state);
		data->sophies[i].dead = 1;
		pthread_mutex_unlock(&data->sophies[i].state);
		i++;
    }
}

static int	who_died(t_omni *data)
{
	int	i;

	i = 0;
	while (i < data->tor->philo_num)
	{
		pthread_mutex_lock(&data->sophies[i].state);
		if (get_time() - data->sophies[i].last_ate > data->tor->time_to_die)
		{
			print_out("has died", &data->tor->timing, data->sophies[i].id, data->tor->start_time);
			data->sophies[i].dead = 1;
			pthread_mutex_unlock(&data->sophies[i].state);
			kill_everyone(data);
			return (1);
		}
		pthread_mutex_unlock(&data->sophies[i].state);
		i++;
	}
	return (0);
}

static int	who_ate(t_omni *data)
{
	int	i;

	i = 0;
	while (i < data->tor->philo_num)
	{
		pthread_mutex_lock(&data->sophies[i].meal_lock);
		if (data->sophies[i].cur_meal == data->tor->meal_num)
		{
			pthread_mutex_lock(&data->sophies[i].state);
			data->sophies[i].dead = 1;
			pthread_mutex_unlock(&data->sophies[i].state);
			pthread_mutex_unlock(&data->sophies[i].meal_lock);
			kill_everyone(data);
			return (1);
		}
		pthread_mutex_unlock(&data->sophies[i].meal_lock);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
    t_omni  *data;

    data = (t_omni *)arg;
	ft_usleep(data->tor->time_to_die / 10, get_time());
	// pthread_mutex_lock(&data->tor->start);
    // while(1)
    // {
	//     pthread_mutex_lock(data->tor->start);
    //     if (data->can_go)
    //     {           
    //         pthread_mutex_unlock(&data->tor->start);
    //         break ;
    //     }
	//     pthread_mutex_unlock(&data->tor->start);
    // }
	// print_out("here left", &data->tor->timing, -2, data->tor->start_time);
	// pthread_mutex_unlock(&data->tor->start);
	while (1)
	{
		// print_out("loop", &data->tor->timing, -2, data->tor->start_time);
		if (who_died(data))
			break ;
		if (who_ate(data));
			break ;
	}
}
