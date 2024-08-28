/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:18 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/28 18:11:22 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void	void_malloc_failed(t_philo *forum)
{
	pthread_mutex_destroy(forum->timing);
	// pthread_mutex_destroy(forum->state);
	printf("Error: Malloc failed.\n");
}

int	init_failed(t_philo *forum, t_philo **sphs, pthread_mutex_t **frks, int i)
{
	// printf("Error: initialisation failed.\n");
	// free(sphs);
	while (--i > -1)
		pthread_mutex_destroy(sphs[i]);
	i = -1;
	while (++i < forum->philo_num)
		pthread_mutex_destroy(frks[i]);
	pthread_mutex_destroy(forum->timing);
}

void	cleanup(t_philo	*forum, t_philo	**sophies, pthread_mutex_t *forks)
{
	pthread_mutex_destroy(forum->timing);
	free(sophies);
	free(forks);
	//check if this works
}
