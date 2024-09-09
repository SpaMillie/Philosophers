/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:00:59 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/04 11:44:50 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static int	eating(t_philo *sopher)
{
	if (sopher->philo_num == 1)
		return (table_4_1(sopher));
	pthread_mutex_lock(sopher->left_fork);
	print_out("has taken a fork", sopher);
	pthread_mutex_lock(sopher->right_fork);
	print_out("has taken a fork", sopher);
	if (!check_state(sopher))
	{
		if (get_time() - sopher->last_ate > sopher->time_to_die)
			return (assassin(sopher, 1));
		else
		{
			sopher->last_ate = print_out("is eating", sopher);
			if (sopher->time_to_die < sopher->time_to_eat)
				return (sudden_death(sopher, 1));
			ft_usleep(sopher, sopher->time_to_eat, sopher->last_ate);
		}
	}
	pthread_mutex_lock(&sopher->meal_lock);
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
			return (assassin(sopher, 0));
		else
		{
			if (sopher->time_to_die < sopher->time_to_sleep)
				return (sudden_death(sopher, 0));
			ft_usleep(sopher, sopher->time_to_sleep, \
				sopher->last_ate + sopher->time_to_eat);
		}
	}
	if (get_time() - sopher->last_ate > sopher->time_to_die)
		return (assassin(sopher, 0));
	return (0);
}

static void	thinking(t_philo *sopher)
{
	print_out("is thinking", sopher);
	if ((sopher->id == 0 || \
		sopher->id % 2 == 0) && sopher->cur_meal == 0)
		ft_usleep(sopher, sopher->time_to_die / 10, sopher->start_time);
}

static void	*life(void *arg)
{
	t_philo	*sopher;

	sopher = (t_philo *)arg;
	pthread_mutex_lock(sopher->start);
	pthread_mutex_unlock(sopher->start);
	while (1)
	{
		if (check_state(sopher))
			break ;
		thinking(sopher);
		if (check_state(sopher))
			break ;
		if (eating(sopher) == 0)
			sleeping(sopher);
	}
	return (NULL);
}

int	philogenesis(t_omni *data)
{
	int	i;

	i = 0;
	data->tor->start_time = lock_time(&data->tor->timing);
	while (i < data->tor->philo_num)
	{
		data->sophies[i].start_time = data->tor->start_time;
		data->sophies[i].last_ate = data->sophies[i].start_time;
		if (pthread_create(&(data->sophies[i].thread), NULL, \
			&life, (void *)&data->sophies[i]) != 0)
		{
			printf("Error: philogenesis failed\n");
			while (--i > -1)
				pthread_join(data->sophies[i].thread, NULL);
			return (1);
		}
		i++;
	}	
	return (0);
}
