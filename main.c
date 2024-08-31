/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/31 11:19:22 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

// int	int_malloc_failed(void)
// {
// 	printf("Error: Malloc failed.\n");
// 	return (-1);
// }

static int	set_philo(t_moni *tor, t_philo *sophy, int i, pthread_mutex_t *fork)
{
	sophy->id = i;
	sophy->philo_num = tor->philo_num;
	sophy->right_fork = &fork[i];
	// pthread_mutex_lock(sophy->right_fork);
	// printf("checking if the right fork can be locked\n");
	// pthread_mutex_unlock(sophy->right_fork);
	if (i == tor->philo_num - 1)
		sophy->left_fork = &fork[0];
	else
		sophy->left_fork = &fork[i + 1];
	// pthread_mutex_lock(sophy->left_fork);
	// printf("checking if the left fork can be locked\n");
	// pthread_mutex_unlock(sophy->left_fork);
	sophy->meal_num = tor->meal_num;
	sophy->time_to_sleep = tor->time_to_sleep;
	sophy->time_to_die = tor->time_to_die;
	sophy->time_to_eat = tor->time_to_eat;
	sophy->timing = &tor->timing;
	// pthread_mutex_lock(&tor->timing);
	// printf("checking if the tor timing can be locked\n");
	// pthread_mutex_unlock(&tor->timing); 	
	// pthread_mutex_lock(sophy->timing);
	// printf("checking if the timing can be locked\n");
	// pthread_mutex_unlock(sophy->timing);
	sophy->start = &tor->start;
	// pthread_mutex_lock(&tor->start);
	// printf("checking if the tor start can be locked\n");
	// pthread_mutex_unlock(&tor->start); 	
	// pthread_mutex_lock(sophy->start);
	// printf("checking if the start can be locked\n");
	// pthread_mutex_unlock(sophy->start);	
	sophy->dead = 0;
	sophy->eating = 0;
	sophy->cur_meal = 0;
	if (mutex_initing(sophy) == -1)
		return (-1);
	// printf("checking %d\n", sophy->id);
 	// pthread_mutex_lock(&sophy->state);
	// printf("checking if the state can be locked\n");
	// pthread_mutex_unlock(&sophy->state);
 	// pthread_mutex_lock(&sophy->meal_lock);
	// printf("checking if the meal_lock can be locked\n");
	// pthread_mutex_unlock(&sophy->meal_lock); 	
	return (0);
}

static int	set_forks(t_moni *tor, t_philo *sophies, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < tor->philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error: initialisation failed.\n");
			free(sophies);
			while (--i > -1)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			pthread_mutex_destroy(&tor->timing);
			pthread_mutex_destroy(&tor->start);
			return (-1);
		}
		// pthread_mutex_lock(&forks[i]);
		// printf("checking fork num %d\n", i);
		// pthread_mutex_unlock(&forks[i]);
	}
	return (0);
}

// void	ft_print(char *str, t_philo *cur_ph, int i)
// {
// 	size_t	cur_time;

// 	cur_time = get_time();
// 	pthread_mutex_lock(&cur_ph->timing);
// 	printf("%lu philosopher %d %s\n", cur_time - cur_ph->start_time, 
// 		cur_ph->id, str);
// 	pthread_mutex_unlock(&cur_ph->timing);
// }

// void	death_ensues(t_philo **sophies, int i, int max)
// {
// 	int	j;

// 	j = -1;
// 	ft_print("died", sophies[i], i);
// 	while (++j < max)
// 		sophies[j]->dead = 1;
// }

static void	start_simulation(t_moni *tor, t_philo *sphs, pthread_mutex_t *frk)
{
	t_omni	data;
	int		i;

	i = -1;
	data.tor = tor;
	data.sophies = sphs;
	data.forks = frk;
	data.can_go = 0;
	pthread_mutex_lock(&tor->start);
	// printf("entered start_ssimulatin\n");
	if (pthread_create(&tor->thread, NULL, &monitoring, (void *)&data) != 0)
	{
		printf("Error: failed to create the monitoring thread\n");
		pthread_mutex_unlock(&tor->start);
		return ;
	}
	else
	{
		if (philogenesis(&data))
		{
			pthread_join(tor->thread, NULL);
			pthread_mutex_unlock(&tor->start);
			return ;
		}
		// printf("exited philogenisis\n");
		pthread_mutex_unlock(&tor->start);
		while (++i < tor->philo_num)
			pthread_join(sphs[i].thread, NULL);
		pthread_join(tor->thread, NULL);
	}
}

static void	start(t_moni *tor, char **argv, int argc)
{
	int	i;
	t_philo *sophies;
	pthread_mutex_t	*forks;

	if (check_args(tor, argv, argc) == -1)
		return ;
	// if (pthread_mutex_lock(&tor->start) == 0)
	// 	printf("checking if the tor start can be locked\n");
	// if (pthread_mutex_unlock(&tor->start) != 0)	
	// 	printf("mutex for sure unlocked\n");
	sophies = malloc(sizeof(t_philo) * tor->philo_num);
	if (!sophies)
		return (void_malloc_failed(tor));
	forks = malloc(sizeof(pthread_mutex_t) * tor->philo_num);
	if (!forks)
	{
		free (sophies);
		return(void_malloc_failed(tor));
	}
	if (set_forks(tor, sophies, forks) == -1)
		return ;
	i = -1;
	while (++i < tor->philo_num)
	{
		if (set_philo(tor, &sophies[i], i, forks) == -1) //check if it cleans up nicely
			return (init_failed(tor, sophies, forks, i));
		// printf("is it here %d\n", sophies[i].id);	
	}
	// pthread_mutex_lock(&sophies[0].state);
	// printf("checking if the state can be locked\n");
	// pthread_mutex_unlock(&sophies[0].state);
 	// pthread_mutex_lock(&sophies[0].meal_lock);
	// printf("checking if the meal_lock can be locked\n");
	// pthread_mutex_unlock(&sophies[0].meal_lock);
	start_simulation(tor, sophies, forks);
	cleanup(tor, sophies, forks);
}

int	main(int argc, char **argv)
{
	t_moni	tor;
	int	i;

	i = 1;
	tor = (t_moni){0};
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (digit_finder(argv[i]) == -1)
			{
				printf("Error: Invalid arguments. Try actual numbers.\n");
				return (0);
			}
			i++;
		}
		start(&tor, argv + 1, argc);
	}
	else
		printf("Error: Invalid number of arguments.\n");
}
