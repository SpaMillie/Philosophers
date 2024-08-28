/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/28 09:57:00 by mspasic          ###   ########.fr       */
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
	int	time_to_die; //dont accept if this is 0
	int	time_to_eat;//dont accept if this is 0 
	int	time_to_sleep;//dont accept if this is 0 
	int	meal_num;//dont accept if this is 0 
	int	dead;
	size_t start_time;
	size_t cur_time;
	size_t last_supper;
	pthread_t	thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*timing;
	pthread_mutex_t	*living;
}	t_philo;

typedef struct s_omni
{
	t_philo *forum;
	t_philo **sophies;
	pthread_mutex_t	**forks;
}	t_omni;


//main.c
//handle_args.c
int		digit_finder(char *str);
int		check_args(t_philo *forum, char **argv, int argc);
//ft_atoi.c
int     ft_atoi(const char *str);
//timing.c
void    ft_usleep(size_t sleep_time);
size_t	get_time(void);
//utils.c
void	void_malloc_failed(void);
int		destroy_mut(pthread_mutex_t *mutex);
int		init_failed(t_philo *sphs, pthread_mutex_t **frks, int i);

#endif
