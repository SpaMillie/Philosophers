/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/23 12:19:03 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

typedef struct s_agora
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_num;
	int	argc;
	int	*forks;
}	t_agora;

typedef struct	s_philo
{
	int	index;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_num;
	int	*right_fork;
	int	*left_fork;
}	t_philo;

//main.c
//ft_atoi.c
int     ft_atoi(const char *str);

#endif
