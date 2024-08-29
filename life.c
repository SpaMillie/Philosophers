/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:00:59 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 16:40:04 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static void    eating(t_philo  *sopher)
{
    pthread_mutex_lock(sopher->left_fork); 
   	pthread_mutex_lock(sopher->right_fork);
   	pthread_mutex_lock(sopher->meal_lock);
    sopher->last_ate = print_out("is eating", sopher);
    while(get_time() - sopher->last_ate < sopher->time_to_eat)
    {
        if (get_time() - sopher->last_ate < sopher->time_to_die)
            break ;
        else
            ft_usleep(100, sopher->last_ate); 
    }
    sopher->meal_num++;
	pthread_mutex_unlock(sopher->meal_lock); 
    pthread_mutex_unlock(sopher->left_fork); 
   	pthread_mutex_unlock(sopher->right_fork);
}

static void	sleeping(t_philo *sopher)
{
	print_out("is sleeping", sopher);
	ft_usleep(sopher->time_to_sleep, sopher->start_time);
}

static void	thinking(t_philo *sopher)
{
	print_out("is thinking", sopher);
	if ((sopher->philo_num == 0 || \
		sopher->philo_num % 2 == 0) && sopher->cur_meal == 0)
		ft_usleep(sopher->time_to_eat / 2, sopher->start_time);
}

static void	*life(void *arg)
{
    t_philo *sopher;

    sopher = (t_philo *)arg;
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
	printf("entered philogenesis\n");
	pthread_mutex_lock(data->forum->start);
	data->forum->start_time = lock_time(data->forum); 
	printf("good philogenesis\n");
	while (++i < data->forum->philo_num)
	{
		data->sophies[i].start_time = data->forum->start_time;
        printf("start time is %lu\n", data->sophies[i].start_time);
		if (pthread_create(&data->sophies[i].thread, NULL, \
			&life, (void *)&data->sophies[i]) != 0)
		{
			printf("Error: philogenesis failed\n");
			while (--i > -1)
			{
                //not needed?
				// pthread_mutex_lock(data->sophies[i]->state);
				// data->sophies[i]->dead = 1;
				// pthread_mutex_unlock(data->sophies[i]->state);
				pthread_join(data->sophies[i].thread, NULL);
			}
            data->can_go = 1;
			pthread_mutex_unlock(data->forum->start);
			return (1);
		}
	}
    printf("every thread created\n");
    data->can_go = 1;
	pthread_mutex_unlock(data->forum->start);
	return (0);
}
