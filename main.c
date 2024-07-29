/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/29 21:10:51 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

// int	int_malloc_failed(void)
// {
// 	printf("Error: Malloc failed.\n");
// 	return (-1);
// }

void	set_philo(t_philo *frm, t_philo *sophy, int i, pthread_mutex_t **fork)
{
	sophy->philo_num = i;
	sophy->right_fork = fork[i];
	if (i == frm->philo_num - 1)
		sophy->left_fork = fork[0];
	else
		sophy->left_fork = fork[i + 1];
	sophy->meal_num = frm->meal_num;
	sophy->time_to_sleep = frm->time_to_sleep;
	sophy->time_to_die = frm->time_to_die;
	sophy->time_to_eat = frm->time_to_eat;
	sophy->start_time = frm->start_time;
	printf("checking %d, %d, %d\n", sophy->time_to_die, sophy->time_to_eat, sophy->time_to_sleep);
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

int	set_forks(t_philo *forum, t_philo **sophies, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	// printf("here\n");
	while (++i < forum->philo_num)
	{
		// printf("here's %p\n", &forks[i]);
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (init_failed(*sophies, &forks, i));
		printf("inited mutex %d\n", i);
	}
	return (0);
}

void	start_simulation(t_philo *frm, t_philo *sphs, pthread_mutex_t *frk)
{

}

static void	start(t_philo *forum, char **argv, int argc)
{
	int	i;
	t_philo *sophies;
	pthread_mutex_t	*forks;

	if (check_args(forum, argv, argc) == -1)
		return ;
	sophies = malloc(sizeof(t_philo) * forum->philo_num);
	if (!sophies)
		return (void_malloc_failed());
	forks = malloc(sizeof(pthread_mutex_t) * forum->philo_num);
	if (!forks)
	{
		free (sophies);
		return(void_malloc_failed());
	}
	if (set_forks(forum, &sophies, forks) == -1)
		return ;
	i = -1;
	while (++i < forum->philo_num)
		set_philo(forum, &sophies[i], i, &forks);
	start_simulation(forum, &sophies, forks);
	free(sophies);
	free(forks);
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
