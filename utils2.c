/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:02:50 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 11:49:38 by mspasic          ###   ########.fr       */
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
