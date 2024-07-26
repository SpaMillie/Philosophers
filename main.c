/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/26 16:27:30 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void	void_malloc_failed(void)
{
	printf("Error: Malloc failed.\n");
}

int	int_malloc_failed(void)
{
	printf("Error: Malloc failed.\n");
	return (-1);
}

static int	digit_finder(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] <= '9' && str[i] >= '0') || (i == 0 && (str[i] == '-' || str[i] == '+')))
			i++;
		else
			return (-1);
	}
}
static void	init_args(int i, int num, t_philo *forum)
{
	if (i == 0)
		forum->philo_num = num;
	else if (i == 1)
		forum->time_to_die = num;
	else if (i == 2)
		forum->time_to_eat = num;
	else if (i == 3)
		forum->time_to_sleep = num;
	else if (i == 4)
		forum->meal_num = num;
}
static int	philo_atoi(char *str, int i, t_philo *forum)
{
	int	num;

	num = ft_atoi(str);
	if (num < 0)
	{
		printf("Error: Arguments contain unacceptable numbers.\n");
		return (-1);
	}
	init_args(i, num, forum);
	return (0);
}

void	assign_philo(t_philo *forum, t_philo *sophy, int i)
{
	sophy->index = i;
	sophy->right_fork = &forum->forks[i];

	 if (i == forum->philo_num - 1)
		sophy->left_fork = &forum->forks[0];
	else
		sophy->left_fork = &forum->forks[i + 1];
	if (forum->argc == 5)
		sophy->meal_num = forum->meal_num;
	else
		sophy->meal_num = -2;
	sophy->time_to_sleep = forum->time_to_sleep;
	sophy->time_to_die = forum->time_to_die;
	sophy->time_to_eat = forum->time_to_eat;
	printf("checking %d, %d, %d\n", sophy->time_to_die, sophy->time_to_eat, sophy->time_to_sleep);
}
int	destroy_mut(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(&mutex) != 0)
	{
		printf("Error: couldn't destroy mutex\n");
		return (1);
	}
	return (0);
}

int	init_failed(t_philo *forum, t_philo *sophies, pthread_mutex_t **forks, int i)
{
	printf("Error: initialisation failed.\n");
	free(sophies);
	while (--i > -1)
	{
		if (destroy_mut(forks[i]) != 0)
			return (1);
	}
	return (0);
}

int	allocate_forks_locks(t_philo *forum, t_philo **sophies, pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	*forks = malloc(sizeof(pthread_mutex_t) * forum->philo_num);
	if (!(*forks))
	{
		free(*sophies);
		return (int_malloc_failed());
	}
	while (++i < forum->philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (init_failed(forum, sophies, forks, i));
		printf("inited mutex %d\n", i);
	}
	return (0);
}

int	check_args(t_philo *forum, char **argv, int argc)
{
	int	i;

	i = -1;
	while (++i < argc - 1)
	{
		if (philo_atoi(argv[i], i, forum) == -1)
			return (-1);
	}
	return (0);
}
void	start_life(t_philo *forum, t_philo *sophies)
{

}

static void	start(t_philo *forum, char **argv, int argc)
{
	int	i;
	t_philo *sophies;
	pthread_mutex_t	*locks;

	if (check_args(forum, argv, argc) == -1)
		return ;
	sophies = malloc(sizeof(t_philo) * forum->philo_num);
	if (!sophies)
		return (void_malloc_failed);
	allocate_forks_locks(forum, &sophies, &locks);
	i = -1;
	while (++i < forum->philo_num)
		assign_philo(forum, &sophies[i], i);
	start_simulation(forum, &sophies);
	free(sophies);
	free(locks);
}

void	cleanup(t_philo *forum)
{
	free(forum->forks);
	free(forum->locks);
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
		cleanup(&forum); //alter
	}
	else
		printf("Error: Invalid number of arguments.\n");
}
