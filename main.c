/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/24 13:00:27 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

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
static void	init_args(int i, int num, t_agora *forum)
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
static int	philo_atoi(char *str, int i, t_agora *forum)
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

void	assign_philo(t_agora *forum, t_philo *sophy, int i)
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

int	allocate_forks_locks(t_agora *forum, t_philo *sophies)
{
	int	i;

	i = -1;
	forum->forks = malloc(sizeof(int) * forum->philo_num);
	if (!forum->forks)
	{
		printf("Error: Malloc failed.\n");
		free(sophies);
		return (-1);
	}
	forum->locks = malloc(sizeof(pthread_mutex_t) * forum->philo_num);
	if (!forum->locks)
	{
		printf("Error: Malloc failed.\n");
		free(sophies);
		free(forum->forks);
		return (-1);
	}
	while (++i < forum->philo_num)
	{
		forum->forks[i] = i;
		printf("allocated %d\n", forum->forks[i]);
	}
	return (0);
}

int	check_args(t_agora *forum, char **argv)
{
	int	i;

	i = -1;
	while (++i < forum->argc)
	{
		if (philo_atoi(argv[i], i, forum) == -1)
			return (-1);
	}
	return (0);
}

static void	start(t_agora *forum, char **argv)
{
	int	i;
	t_philo *sophies;

	if (check_args(forum, argv) == -1)
		return ;
	sophies = malloc(sizeof(t_philo) * forum->philo_num);
	if (!sophies)
	{
		printf("Error: Malloc failed.\n");
		return ;
	}
	allocate_forks_locks(forum, sophies);
	i = -1;
	while (++i < forum->philo_num)
		assign_philo(forum, &sophies[i], i);
	free(sophies);
}

void	cleanup(t_agora *forum)
{
	free(forum->forks);
	free(forum->locks);
}

int	main(int argc, char **argv)
{
	t_agora	forum;
	int	i;

	i = 1;
	forum = (t_agora){0};
	if (argc == 5)
		forum.argc = 4;
	else if (argc == 6)
		forum.argc = 5;
	if (argc == 5 || argc == 6)
	{
		while (i < forum.argc + 1)
		{
			if (digit_finder(argv[i]) == -1)
			{
				printf("Error: Invalid arguments. Try actual numbers.\n");
				return (0);
			}
			i++;
		}
		start(&forum, argv + 1);
		cleanup(&forum);
	}
	else
		printf("Error: Invalid number of arguments.\n");
}
