/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:07:58 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 13:42:00 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static void	kill_everyone(t_omni *data)
{
	int	i;

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
		if (data->sophies[i].dead == 1 || (data->sophies[i].cur_meal != 0 && \
			get_time() - data->sophies[i].last_ate > data->tor->time_to_die))
		{
			if (data->sophies[i].dead == 0)
			{
				print_out("has died", &data->sophies[i]);
				change_stop(&data->sophies[i]);
				data->sophies[i].dead = 1;
			}
			pthread_mutex_unlock(&data->sophies[i].state);
			kill_everyone(data);
			return (1);
		}
		pthread_mutex_unlock(&data->sophies[i].state);
		i++;
	}
	return (0);
}

static void	ft_full(t_philo *sopher)
{
	pthread_mutex_lock(&sopher->state);
	sopher->dead = 1;
	pthread_mutex_unlock(&sopher->state);
}

static int	who_ate(t_omni *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->tor->meal_num != -2 && i < data->tor->philo_num)
	{
		pthread_mutex_lock(&data->sophies[i].meal_lock);
		if (data->sophies[i].cur_meal >= data->tor->meal_num)
			count++;
		if (count == data->tor->philo_num)
		{
			ft_full(&data->sophies[i]);
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
	t_omni	*data;

	data = (t_omni *)arg;
	while (1)
	{
		if (who_died(data) == 1)
			break ;
		if (who_ate(data) == 1)
			break ;
	}
}
