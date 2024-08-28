/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:12:17 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/28 18:14:18 by mspasic          ###   ########.fr       */
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
