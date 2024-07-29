/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/29 21:22:31 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	start_time;
	int	last_ate;
	int	meal_num;
	int	flag_means_death;
	pthread_t	thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

//main.c
//args.c
int	digit_finder(char *str);
int	check_args(t_philo *forum, char **argv, int argc);
//ft_atoi.c
int     ft_atoi(const char *str);
//utils.c
void	void_malloc_failed(void);

#endif
