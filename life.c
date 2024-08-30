/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:00:59 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/30 17:07:42 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static void    eating(t_philo  *sopher)
{
    pthread_mutex_lock(sopher->left_fork); 
   	pthread_mutex_lock(sopher->right_fork);
   	pthread_mutex_lock(&sopher->meal_lock);
    sopher->last_ate = print_out("is eating", sopher->timing, sopher->philo_num);
    while(get_time() - sopher->last_ate < sopher->time_to_eat)
    {
        if (get_time() - sopher->last_ate < sopher->time_to_die)
            break ;
        else
            ft_usleep(100, sopher->last_ate); 
    }
    sopher->meal_num++;
	pthread_mutex_unlock(&sopher->meal_lock); 
    pthread_mutex_unlock(sopher->left_fork); 
   	pthread_mutex_unlock(sopher->right_fork);
}

static void	sleeping(t_philo *sopher)
{
	print_out("is sleeping", sopher->timing, sopher->philo_num);
	ft_usleep(sopher->time_to_sleep, sopher->start_time);
}

static void	thinking(t_philo *sopher)
{
	print_out("is thinking", sopher->timing, sopher->philo_num);
	if ((sopher->philo_num == 0 || \
		sopher->philo_num % 2 == 0) && sopher->cur_meal == 0)
		ft_usleep(sopher->time_to_eat / 2, sopher->start_time);
}

static void	*life(void *arg)
{
    t_philo *sopher;

    sopher = (t_philo *)arg;
	printf("%d has been born\n", sopher->philo_num);
	pthread_mutex_lock(sopher->start);
	printf("philo locked the start\n"); 
	pthread_mutex_unlock(sopher->start);
	printf("philo unlocked the start\n");
	printf("%d\n", check_state(sopher)); 
	while(!check_state)
	{
		printf("life started\n");
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
	pthread_mutex_lock(&data->tor->start);
	printf("start locked\n");
	data->tor->start_time = lock_time(&data->tor->timing); 
	printf("good philogenesis\n");
	while (++i < data->tor->philo_num)
	{
		data->sophies[i].start_time = data->tor->start_time;
        printf("philo is %d and start time is %lu\n", data->sophies[i].philo_num, data->sophies[i].start_time);
		if (pthread_create(&(data->sophies[i].thread), NULL, \
			&life, (void *)&data->sophies[i]) != 0)
		{
			printf("Error: philogenesis failed\n");
			while (--i > -1)
				pthread_join(data->sophies[i].thread, NULL);
            data->can_go = 1;
			pthread_mutex_unlock(&data->tor->start);
			return (1);
		}
	}
    printf("every thread created\n");
    data->can_go = 1;
	printf("data is now %d\n", data->can_go);
	pthread_mutex_unlock(&data->tor->start);
	printf("start unlocked\n");
	return (0);
}
