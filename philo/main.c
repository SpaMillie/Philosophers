/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/11 12:29:29 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

static int	set_philo(t_moni *tor, t_philo *sophy, int i, pthread_mutex_t *fork)
{
	sophy->id = i;
	sophy->philo_num = tor->philo_num;
	sophy->right_fork = &fork[i];
	if (i == tor->philo_num - 1)
		sophy->left_fork = &fork[0];
	else
		sophy->left_fork = &fork[i + 1];
	sophy->meal_num = tor->meal_num;
	sophy->time_to_sleep = tor->time_to_sleep;
	sophy->time_to_die = tor->time_to_die;
	sophy->time_to_eat = tor->time_to_eat;
	sophy->timing = &tor->timing;
	sophy->stop = &tor->stop;
	sophy->start = &tor->start;
	sophy->print = &tor->print;
	sophy->dead = 0;
	sophy->cur_meal = 0;
	if (mutex_initing(sophy) == -1)
		return (-1);
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
			pthread_mutex_destroy(&tor->print);
			return (-1);
		}
	}
	return (0);
}

static void	start_simulation(t_moni *tor, t_philo *sphs)
{
	t_omni	data;

	data.tor = tor;
	data.sophies = sphs;
	pthread_mutex_lock(&tor->start);
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
			return ;
		}	
		sim_cleanup(tor, sphs);
	}
}

static void	start(t_moni *tor, char **argv, int argc)
{
	int				i;
	t_philo			*sophies;
	pthread_mutex_t	*forks;

	if (check_args(tor, argv, argc) == -1)
		return ;
	sophies = malloc(sizeof(t_philo) * tor->philo_num);
	if (!sophies)
		return (void_malloc_failed(tor));
	forks = malloc(sizeof(pthread_mutex_t) * tor->philo_num);
	if (!forks)
	{
		free (sophies);
		return (void_malloc_failed(tor));
	}
	if (set_forks(tor, sophies, forks) == -1)
		return ;
	i = -1;
	while (++i < tor->philo_num)
	{
		if (set_philo(tor, &sophies[i], i, forks) == -1)
			return (init_failed(tor, sophies, forks, i));
	}
	start_simulation(tor, sophies);
	cleanup(tor, sophies, forks);
}

int	main(int argc, char **argv)
{
	t_moni	tor;
	int		i;

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
