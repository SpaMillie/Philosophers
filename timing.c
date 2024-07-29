/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:12:17 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/29 21:51:11 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long get_time(void)
{
    unsigned long long  millisec;
    struct timeval   tv;
 
    gettimeofday(&tv, NULL);
    millisec = tv.tv_sec * 1000 + tv.tv_usec * 0.001;
    return (millisec);
}
