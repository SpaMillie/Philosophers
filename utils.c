/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:18 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 10:36:27 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void	void_malloc_failed(t_moni *tor)
{
	pthread_mutex_destroy(&tor->timing);
	// pthread_mutex_destroy(tor->state);
	printf("Error: Malloc failed.\n");
}

void	init_failed(t_moni *tor, t_philo *sphs, pthread_mutex_t *frks, int i)
{
	// printf("Error: initialisation failed.\n");
	// free(sphs);
	while (--i > -1)
	{
		pthread_mutex_destroy(&sphs[i].state);
		pthread_mutex_destroy(&sphs[i].meal_lock);
	}
	free(sphs);
	i = -1;
	while (++i < tor->philo_num)
		pthread_mutex_destroy(&frks[i]);
	free(frks);
	pthread_mutex_destroy(&tor->start);
	pthread_mutex_destroy(&tor->timing);
}

void	cleanup(t_moni	*tor, t_philo	*sophies, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < tor->philo_num)
		pthread_mutex_destroy(&forks[i++]); 
	pthread_mutex_destroy(&tor->timing);
	pthread_mutex_destroy(&tor->start);
	free(sophies);
	free(forks);
	//check if this works by freeing it in the previous function too (double-free complaint)
}

size_t	print_out(char *str, t_philo *sopher)
{
	size_t	cur_time;

	cur_time = lock_time(sopher->timing);
	if (check_stop(sopher) != 1)
		printf("%lu %d %s\n", cur_time - sopher->start_time, sopher->id + 1, str);
	return (cur_time);
}

// void	up_meal_num(t_philo *sopher)
// {
// 	pthread_mutex_lock(&sopher->meal_lock);
// 	sopher->cur_meal++;
// 	pthread_mutex_unlock(&sopher->meal_lock);
// }
