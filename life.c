/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:00:59 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 13:10:47 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"


void    eating(t_philo  *sophie)
{
//add this
}

void	sleeping(t_philo *sopher)
{
	print_out("is sleeping", sopher);
	ft_usleep(sopher->time_to_sleep, sopher->start_time);
}

void	thinking(t_philo *sopher)
{
	print_out("is thinking", sopher);
	if ((sopher->philo_num == 0 || \
		sopher->philo_num % 2 == 0) && sopher->cur_meal == 0)
		ft_usleep(sopher->time_to_eat / 2, sopher->start_time);
}

void	life(t_philo *sopher)
{
	pthread_mutex_lock(sopher->start);
	pthread_mutex_unlock(sopher->start);
	while(!check_state)
		{
			thinking(sopher);
			if (!check_state)
				eating(sopher);
			if (!check_state)
				sleeping(sopher);
		}
}

int	philogenesis(t_omni *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(data->forum->start);
	data->forum->start_time = lock_time(data->forum); 
	while (++i < data->forum->philo_num)
	{
		data->sophies[i]->start_time = data->forum->start_time;
		if (pthread_create(&data->sophies[i]->thread, NULL, \
			&life, data->sophies[i]) != 0)
		{
			printf("Error: philogenesis failed\n");
			while (--i > -1)
			{
				pthread_mutex_lock(data->sophies[i]->state);
				data->sophies[i]->dead = 1;
				pthread_mutex_unlock(data->sophies[i]->state);
				pthread_join(data->sophies[i], NULL);
				pthread_mutex_unlock(data->forum->start);
			}
			return (1);
		}
	}
	pthread_mutex_unlock(data->forum->start);
	return (0);
}
