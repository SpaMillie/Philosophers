/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:12:17 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 10:19:16 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

size_t  get_time(void)
{
    size_t  millisec;
    struct timeval   tv;
 
    gettimeofday(&tv, NULL);
    millisec = tv.tv_sec * 1000 + tv.tv_usec * 0.001;
    return (millisec);
}

void    ft_usleep(size_t sleep_time)
{
    size_t  start;

    start = get_time();
    while (get_time() - start < sleep_time)
        usleep(500);
}

size_t  lock_time(t_philo *forum)
{
    size_t  cur_time;

	pthread_mutex_lock(forum->timing);
    cur_time = get_time();
    pthread_mutex_unlock(forum->timing);
    return (cur_time);
}
