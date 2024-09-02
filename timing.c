/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:12:17 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 10:33:07 by mspasic          ###   ########.fr       */
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

void    ft_usleep(size_t sleep_time, size_t start)
{
    while (get_time() - start < sleep_time)
        usleep(500);
}

size_t  lock_time(pthread_mutex_t *cur)
{
    size_t  cur_time;

	pthread_mutex_lock(cur);
    cur_time = get_time();
    pthread_mutex_unlock(cur);
    return (cur_time);
}

void    change_stop(t_philo *sopher)
{
	pthread_mutex_lock(sopher->start);
    *sopher->stop = 1;
    pthread_mutex_unlock(sopher->start);
}
