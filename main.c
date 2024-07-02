/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/02 12:54:20 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//make h file
#include <stdio.h>

typedef struct s_agora
{
	int	philo_num;
	int	**time_to_die;
	int	**time_to_eat;
	int	**time_to_sleep;
	int	meal_num;
	int	argc;
}	t_agora;


int	check_args(t_agora *forum, char **argv)
{
	int	i;

	i = 0;
	while (argv[i] < forum->argc)
	{
		if (philo_atoi(argv[i]) == -1)
			return (-1);
	}

}

void	start(t_agora *forum, char **argv)
{
	// int	check;


	if (check_args == -1)
		return (err_invalid);
}

int	main(int argc, char **argv)
{
	t_agora	forum;

	forum = (t_agora){0};
	if (argc == 5)
		forum.argc = 4;
	else if (argc == 6)
		forum.argc = 5;
	if (argc == 5 || argc == 6)
	{
		start(&forum, argv + 1);
	}
	else
		printf("Woah there! Please give 4 or 5 arguments only!\n");
}
