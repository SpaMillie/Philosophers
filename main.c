/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/02 02:27:18 by mspasic          ###   ########.fr       */
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
}	t_agora;


int	phil_atoi(int argc, char **argv)
{
	
}

void	start(int argc, char **argv)
{
	// int	check;

	if (phil_atoi == -1)
		return (err_invalid);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		start(argc, argv + 1);
	}
	else
		printf("Woah there! Please give 4 or 5 arguments only!\n");
}
