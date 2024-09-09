/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:02:50 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/04 11:44:16 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

int	sudden_death(t_philo *sopher, int eat_sleep)
{
	ft_usleep(sopher, sopher->time_to_die, sopher->last_ate);
	assassin(sopher, 0);
	if (eat_sleep == 1)
	{
		pthread_mutex_unlock(sopher->right_fork);
		pthread_mutex_unlock(sopher->left_fork);
	}
	return (1);
}

int	assassin(t_philo *sopher, int eat_sleep)
{
	pthread_mutex_lock(&sopher->state);
	print_out("has died", sopher);
	change_stop(sopher);
	sopher->dead = 1;
	pthread_mutex_unlock(&sopher->state);
	if (eat_sleep == 1)
	{
		pthread_mutex_unlock(sopher->right_fork);
		pthread_mutex_unlock(sopher->left_fork);
	}
	return (1);
}

int	table_4_1(t_philo *sopher)
{
	pthread_mutex_lock(sopher->left_fork);
	print_out("has taken a fork", sopher);
	ft_usleep(sopher, sopher->time_to_die, sopher->start_time);
	assassin(sopher, 0);
	pthread_mutex_unlock(sopher->left_fork);
	return (1);
}

void	sim_cleanup(t_moni *tor, t_philo *sphs)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&tor->start);
	while (i < tor->philo_num)
	{
		pthread_join(sphs[i].thread, NULL);
		i++;
	}
	pthread_join(tor->thread, NULL);
}
