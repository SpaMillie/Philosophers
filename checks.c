/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:48:09 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/30 09:42:54 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"


// int	check_appetite(t_omni *data)
// {
// 	int	i;

// 	i = 0;
// 	if (data->forum->meal_num == -2)
// 		return (0);
// 	while (i < data->forum->philo_num)
// 	{
// 		if (data->sophies[i]->meal_num)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	check_death(t_omni *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->forum->philo_num)
// 	{
// 		pthread_mutex_lock(&data->sophies[i]->state);
// 		if (data->sophies[i]->dead == 1)
// 		{
// 			death_ensues(data->sophies, i, \
// 				data->forum->philo_num);
// 			return (1) ;
// 		}
// 		pthread_mutex_lock(&data->sophies[i]->state);
// 		i++;
// 	}
// 	return (0);
// }

pthread_mutex_t	*mutex_initing(void)
{
	pthread_mutex_t	cur;
	pthread_mutex_t	*current;

	if (pthread_mutex_init(&cur, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		pthread_mutex_destroy(&cur);
		return (NULL);
	}
	pthread_mutex_lock(&cur);
	printf("locked the current mutex\n");
	pthread_mutex_unlock(&cur);
	current = &cur;
	return (current);
}

int	check_meal_num(t_philo *sopher)
{
	pthread_mutex_lock(sopher->meal_lock);
	if (sopher->cur_meal == sopher->meal_num)
	{
		pthread_mutex_lock(sopher->state);
		sopher->dead = 1;
		pthread_mutex_unlock(sopher->state);
	}
	pthread_mutex_unlock(sopher->meal_lock);
}

int	check_state(t_philo *sopher)
{
	int	cur_state;

	pthread_mutex_lock(sopher->state);
	cur_state = sopher->dead;
	pthread_mutex_unlock(sopher->meal_lock);
	return (cur_state);
}
