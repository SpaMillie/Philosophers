/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/06/30 17:13:34 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//make h file
#include <stdio.h>

void	start(int argc, char **argv)
{



int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		start(argc, argv + 1);
	}
	else
		printf("Woah there! Please give 4 or 5 arguments only!\n");
}
