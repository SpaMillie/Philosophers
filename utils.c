/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:18 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/30 17:34:54 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	void_malloc_failed(void)
{
	printf("Error: Malloc failed.\n");
}

int	destroy_mut(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		printf("Error: couldn't destroy mutex\n");
		return (1);
	}
	return (0);
}

int	init_failed(t_philo *sphs, pthread_mutex_t **frks, int i)
{
	printf("Error: initialisation failed.\n");
	free(sphs);
	while (--i > -1)
	{
		if (destroy_mut(frks[i]) != 0)
			return (1);
	}
	return (0);
}
