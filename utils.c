/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:18 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/02 13:45:07 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void	void_malloc_failed(t_moni *tor)
{
	pthread_mutex_destroy(&tor->timing);
	printf("Error: Malloc failed.\n");
}

void	init_failed(t_moni *tor, t_philo *sphs, pthread_mutex_t *frks, int i)
{
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
}

size_t	print_out(char *str, t_philo *sopher)
{
	size_t	cur_time;

	cur_time = lock_time(sopher->timing);
	if (check_stop(sopher) != 1)
		printf("%lu %d %s\n", cur_time - sopher->start_time, \
			sopher->id + 1, str);
	return (cur_time);
}
