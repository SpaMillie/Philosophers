/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:39:14 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/28 09:54:30 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	digit_finder(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] <= '9' && str[i] >= '0') || \
			(i == 0 && (str[i] == '-' || str[i] == '+')))
			i++;
		else
			return (-1);
	}
}

int	mutex_initing(pthread_mutex_t *current)
{
	pthread_mutex_t	cur;

	if (pthread_mutex_init(&cur, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		if (destroy_mut(&cur) != 0)
			return (1);
	}
	current = &cur;
	return (0);	
}
//change and apply to mutex_initing
int	mutex_print_eat(t_philo *forum)
{
	pthread_mutex_t	timing;

	if (pthread_mutex_init(&timing, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		if (destroy_mut(&timing) != 0)
			return (1);
	}
	forum->timing = &timing;
	return (0);
}

static int	init_args(int i, int num, t_philo *forum)
{
	if (i == 0)
		forum->philo_num = num;
	else if (i == 1)
		forum->time_to_die = num;
	else if (i == 2)
		forum->time_to_eat = num;
	else if (i == 3)
	{
		forum->time_to_sleep = num;
		forum->meal_num = -2;
	}
	else if (i == 4)
		forum->meal_num = num;
	forum->start_time = get_time();
	return(mutex_print_eat(forum));
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
	return(init_args(i, num, forum) == 1);
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
