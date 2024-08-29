/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:18 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 14:18:15 by mspasic          ###   ########.fr       */
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
	{
		pthread_mutex_destroy(sphs[i]->state);
		pthread_mutex_destroy(sphs[i]->meal_lock);
		free(sphs[i]);
	}
	i = -1;
	while (++i < forum->philo_num)
		pthread_mutex_destroy(frks[i]);
	free(frks);
	pthread_mutex_destroy(forum->start);
	pthread_mutex_destroy(forum->timing);
}

void	cleanup(t_philo	*forum, t_philo	**sophies, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < forum->philo_num)
		pthread_mutex_destroy(&forks[i++]); //if this doesnt work then neither does the other thing
	pthread_mutex_destroy(forum->timing);
	pthread_mutex_destroy(forum->start);
	free(sophies);
	free(forks);
	//check if this works by freeing it in the previous function too (double-free complaint)
}

size_t	print_out(char *str, t_philo *sopher)
{
	size_t	cur_time;

	cur_time = lock_time(sopher);
	printf("%lu %d %s\n", cur_time, sopher->philo_num, str);
	return (cur_time);
}

void	up_meal_num(t_philo *sopher)
{
	pthread_mutex_lock(sopher->meal_lock);
	sopher->cur_meal++;
	pthread_mutex_unlock(sopher->meal_lock);
}
