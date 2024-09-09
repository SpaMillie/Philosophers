/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:39:14 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/03 09:12:52 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

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
	return (0);
}

static int	mutex_print_state(t_moni *tor)
{
	if (pthread_mutex_init(&tor->timing, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		return (-1);
	}
	if (pthread_mutex_init(&tor->start, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		pthread_mutex_destroy(&tor->timing);
		return (-1);
	}
	if (pthread_mutex_init(&tor->print, NULL) != 0)
	{
		printf("Error: initialisation failed.\n");
		pthread_mutex_destroy(&tor->timing);
		pthread_mutex_destroy(&tor->start);
		return (-1);
	}
	return (0);
}

static void	init_args(int i, int num, t_moni *tor)
{
	if (i == 0)
		tor->philo_num = num;
	else if (i == 1)
		tor->time_to_die = num;
	else if (i == 2)
		tor->time_to_eat = num;
	else if (i == 3)
	{
		tor->time_to_sleep = num;
		tor->meal_num = -2;
	}
	else if (i == 4)
		tor->meal_num = num;
}

static int	philo_atoi(char *str, int i, t_moni *tor)
{
	int	num;

	num = ft_atoi(str);
	if (num <= 0)
	{
		printf("Error: Arguments contain unacceptable numbers.\n");
		return (-1);
	}
	init_args(i, num, tor);
	return (0);
}

int	check_args(t_moni *tor, char **argv, int argc)
{
	int	i;

	i = -1;
	while (++i < argc - 1)
	{
		if (philo_atoi(argv[i], i, tor) == -1)
			return (-1);
	}
	tor->stop = 0;
	if (mutex_print_state(tor) != 0)
		return (-1);
	return (0);
}
