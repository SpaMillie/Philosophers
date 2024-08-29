/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 09:45:56 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//dont forget to remove fsanitize and put everything in a philo directory


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
	int	dead; //flag for state
	int	eating; //for meal num change flag
	size_t start_time;
	size_t cur_time;
	size_t last_ate;
	pthread_t	thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*timing;
	pthread_mutex_t	*state; //init
	pthread_mutex_t	*start;
	pthread_mutex_t	*meal_lock;
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
void	void_malloc_failed(t_philo *forum);
int		init_failed(t_philo *forum, t_philo *sphs, pthread_mutex_t **frks, int i);
void	cleanup(t_philo	*forum, t_philo	**sophies, pthread_mutex_t *forks);

#endif
