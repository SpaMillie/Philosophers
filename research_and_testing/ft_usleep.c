/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:42:44 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/01 13:19:56 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

//usleep function is not as precise as one would want
//it makes the thread sleep for at least x time
//testing and making of a more precise function
size_t ft_gettime(void)
{	
	size_t res = 0;
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
    gettimeofday(&tv, NULL);
	res = tv.tv_sec * 1000 + tv.tv_usec * 0.001;
    return (res);
}

void    ft_usleep(size_t sleep_time)
{
    size_t  start;

    start = ft_gettime();
    while (ft_gettime() - start < sleep_time)
        usleep(500);
}

int main(void)
{
    size_t  start;
    size_t  cur;

    start = ft_gettime();
    printf("cur time is %lu\n", start);
    ft_usleep(1400);
    cur = ft_gettime();
    printf("cur time is %lu\n", cur);
    printf("elapsed time is %lu\n", cur - start);
}
