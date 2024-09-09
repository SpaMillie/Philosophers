/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:48:09 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/03 09:11:44 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

int	mutex_initing(t_philo *sophy)
{
	if (pthread_mutex_init(&sophy->state, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		pthread_mutex_destroy(&sophy->state);
		return (-1);
	}
	if (pthread_mutex_init(&sophy->meal_lock, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		pthread_mutex_destroy(&sophy->state);
		pthread_mutex_destroy(&sophy->meal_lock);
		return (-1);
	}
	return (0);
}

int	check_state(t_philo *sopher)
{
	int	cur_state;

	pthread_mutex_lock(&sopher->state);
	cur_state = sopher->dead;
	pthread_mutex_unlock(&sopher->state);
	return (cur_state);
}

int	check_stop(t_philo *sopher)
{
	int	cur_state;

	pthread_mutex_lock(sopher->start);
	cur_state = *sopher->stop;
	pthread_mutex_unlock(sopher->start);
	return (cur_state);
}
