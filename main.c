/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/30 10:20:11 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

// int	int_malloc_failed(void)
// {
// 	printf("Error: Malloc failed.\n");
// 	return (-1);
// }

static int	set_philo(t_philo *frm, t_philo sophy, int i, pthread_mutex_t *fork)
{
	sophy.philo_num = i; //dnt forget that this isnt total philo_num
	sophy.right_fork = &fork[i];
	pthread_mutex_lock(sophy.right_fork);
	printf("checking if the right fork can be locked\n");
	pthread_mutex_unlock(sophy.right_fork);
	if (i == frm->philo_num - 1)
		sophy.left_fork = &fork[0];
	else
		sophy.left_fork = &fork[i + 1];
	pthread_mutex_lock(sophy.left_fork);
	printf("checking if the left fork can be locked\n");
	pthread_mutex_unlock(sophy.left_fork);
	sophy.meal_num = frm->meal_num;
	sophy.time_to_sleep = frm->time_to_sleep;
	sophy.time_to_die = frm->time_to_die;
	sophy.time_to_eat = frm->time_to_eat;
	sophy.timing = frm->timing;
	pthread_mutex_lock(frm->timing);
	printf("checking if the forum timing can be locked\n");
	pthread_mutex_unlock(frm->timing); 	
	pthread_mutex_lock(sophy.timing);
	printf("checking if the timing can be locked\n");
	pthread_mutex_unlock(sophy.timing);
	sophy.start = frm->start;
	pthread_mutex_lock(frm->start);
	printf("checking if the forum start can be locked\n");
	pthread_mutex_unlock(frm->start); 	
	pthread_mutex_lock(sophy.start);
	printf("checking if the start can be locked\n");
	pthread_mutex_unlock(sophy.start);	
	sophy.dead = 0;
	sophy.eating = 0;
	sophy.cur_meal = 0;
	printf("checking %d, %d, %d\n", sophy.time_to_die, sophy.time_to_eat, sophy.time_to_sleep);
	sophy.state = mutex_initing();
	if (!sophy.state)
		return (-1);
	sophy.meal_lock = mutex_initing();
	if (!sophy.meal_lock)
	{
		pthread_mutex_destroy(sophy.state);
		return (-1);
	}
 	pthread_mutex_lock(sophy.state);
	printf("checking if the state can be locked\n");
	pthread_mutex_unlock(sophy.state);
 	pthread_mutex_lock(sophy.meal_lock);
	printf("checking if the meal_lock can be locked\n");
	pthread_mutex_unlock(sophy.meal_lock); 	
	return (0);
}

static int	set_forks(t_philo *forum, t_philo *sophies, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < forum->philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error: initialisation failed.\n");
			free(sophies);
			while (--i > -1)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			pthread_mutex_destroy(forum->timing);
			pthread_mutex_destroy(forum->start);
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
// 		cur_ph->philo_num, str);
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

static void	start_simulation(t_philo *frm, t_philo *sphs, pthread_mutex_t *frk)
{
	t_omni	data;
	int		i;

	i = -1;
	data.forum = frm;
	data.sophies = sphs;
	data.forks = frk;
	data.can_go = 0;
	printf("entered start_ssimulatin\n");
	if (pthread_create(&frm->thread, NULL, &monitoring, (void *)&data) != 0)
		printf("Error: failed to create the monitoring thread\n");
	else
	{
		if (philogenesis(&data))
		{
			pthread_join(frm->thread, NULL);
			return ;
		}
		printf("exited philogenisis\n");
		while (++i < frm->philo_num)
				pthread_join(sphs[i].thread, NULL);
		pthread_join(frm->thread, NULL);
	}
}

static void	start(t_philo *forum, char **argv, int argc)
{
	int	i;
	t_philo *sophies;
	pthread_mutex_t	*forks;

	if (check_args(forum, argv, argc) == -1)
		return ;
	pthread_mutex_lock(forum->start);
	printf("checking if the forum start can be locked\n");
	pthread_mutex_unlock(forum->start); 	
	printf("mutex for sure unlocked\n");
	sophies = malloc(sizeof(t_philo) * forum->philo_num);
	if (!sophies)
		return (void_malloc_failed(forum));
	forks = malloc(sizeof(pthread_mutex_t) * forum->philo_num);
	if (!forks)
	{
		free (sophies);
		return(void_malloc_failed(forum));
	}
	if (set_forks(forum, sophies, forks) == -1)
		return ;
	i = -1;
	while (++i < forum->philo_num)
	{
		if (set_philo(forum, sophies[i], i, forks) == -1) //check if it cleans up nicely
			return (init_failed(forum, sophies, forks, i));	
	}
	start_simulation(forum, sophies, forks);
	cleanup(forum, sophies, forks);
}

int	main(int argc, char **argv)
{
	t_philo	forum;
	int	i;

	i = 1;
	forum = (t_philo){0};
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
		start(&forum, argv + 1, argc);
	}
	else
		printf("Error: Invalid number of arguments.\n");
}
