/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:39:14 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/29 20:41:46 by mspasic          ###   ########.fr       */
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

static void	init_args(int i, int num, t_philo *forum)
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
	forum->start_time = //GETTIME
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
