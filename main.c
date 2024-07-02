/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/02 19:34:44 by mspasic          ###   ########.fr       */
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
		printf("num is %d\n", num);
		printf("Sorry! The philosophers find these 'numbers' unacceptable.\n");
		return (-1);
	}
	init_args(i, num, forum);
	printf("there are %d philos, dying %d, eating %d, sleeping %d\n", forum->philo_num, forum->time_to_die, forum->time_to_eat, forum->time_to_sleep);
	if (i == 4)
		printf("plus eating for %d times\n", forum->meal_num);
	return (0);
}

static void	start(t_agora *forum, char **argv)
{
	int	i;

	i = 0;
	while (i < forum->argc)
	{
		if (philo_atoi(argv[i], i, forum) == -1)
			return ;
		i++;
	}
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
				printf("Sorry! The philosophers accept only normal-looking numbers.\n");
				return (0);
			}
			i++;
		}
		printf("Arguments valid (for now)\n");
		start(&forum, argv + 1);
	}
	else
		printf("Sorry! The philosophers accept only 4 or 5 arguments!\n");
}
