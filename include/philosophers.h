/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/30 20:53:05 by mspasic          ###   ########.fr       */
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
	int	meal_num;
	int	flag_means_death;
	size_t start_time;
	size_t cur_time;
	size_t last_supper;
	pthread_t	thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*eating;
}	t_philo;

typedef struct s_brief
{
	t_philo *forum;
	t_philo *sophies;
	pthread_mutex_t	*forks;
}	t_brief;


//main.c
//handle_args.c
int		digit_finder(char *str);
int		check_args(t_philo *forum, char **argv, int argc);
//ft_atoi.c
int     ft_atoi(const char *str);
//timing.c
size_t	get_time(void);
//utils.c
void	void_malloc_failed(void);
int		destroy_mut(pthread_mutex_t *mutex);
int		init_failed(t_philo *sphs, pthread_mutex_t **frks, int i);

#endif
