/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:02:50 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 13:36:01 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

int sudden_death(t_philo *sopher, int eat_sleep)
{
	ft_usleep(sopher->time_to_die, sopher->last_ate);
    assassin(sopher);
    if (eat_sleep == 1)
    {
	    pthread_mutex_unlock(&sopher->meal_lock); 
    	pthread_mutex_unlock(sopher->right_fork); 
   	    pthread_mutex_unlock(sopher->left_fork);
        // printf("everything unlocked\n");
    }
    return (1);
}

int	assassin(t_philo *sopher)
{
	pthread_mutex_lock(&sopher->state);
	print_out("has died", sopher);
	change_stop(sopher);
	sopher->dead = 1;
	pthread_mutex_unlock(&sopher->state);	
	return (1);
}

int	table_4_1(t_philo *sopher)
{
    pthread_mutex_lock(sopher->left_fork);
	print_out("has taken a fork", sopher); 
	ft_usleep(sopher->time_to_die, sopher->start_time);
	assassin(sopher);
	return (1);
}

void    sim_cleanup(t_moni *tor, t_philo *sphs, pthread_mutex_t *frk)
{
    int i;

    i = 0;
	pthread_mutex_unlock(&tor->start);
    while (i < tor->philo_num)
    {
        pthread_join(sphs[i].thread, NULL);
        i++;
    }
    pthread_join(tor->thread, NULL);
}
