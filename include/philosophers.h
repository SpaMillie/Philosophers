/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/29 16:26:05 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//dont forget to remove fsanitize and put everything in a philo directory


#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_philo
{
	int	philo_num;
	int	time_to_die; 
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_num;
	int	cur_meal;
	int	dead; //flag for state
	int	eating; //for meal num change flag
	size_t start_time;
	size_t cur_time; //not needed?
	size_t last_ate;
	pthread_t	thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*timing;
	pthread_mutex_t	*start;
	pthread_mutex_t	*state; //init
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_omni
{
	t_philo *forum;
	t_philo *sophies;
	pthread_mutex_t	*forks;
	int	can_go;
}	t_omni;

/*	ALL (NON-STATIC) FUNCTIONS	*/        //ALSO YOU NEED TO MAKE THEM STATIC IF THEY NEED TO BE STATIC

//main.c
//handle_args.c
int		digit_finder(char *str);
// int		mutex_print_state(t_philo *forum);
int		check_args(t_philo *forum, char **argv, int argc);
//ft_atoi.c
int     ft_atoi(const char *str);
//timing.c
void    ft_usleep(size_t sleep_time, size_t start);
size_t	get_time(void);
size_t  lock_time(t_philo *forum);
//utils.c
void	void_malloc_failed(t_philo *forum);
void	init_failed(t_philo *forum, t_philo *sphs, pthread_mutex_t *frks, int i);
void	cleanup(t_philo	*forum, t_philo	*sophies, pthread_mutex_t *forks);
size_t	print_out(char *str, t_philo *sopher);
void	up_meal_num(t_philo *sopher);
//checks.c
int		mutex_initing(pthread_mutex_t *current);
int		check_state(t_philo *sopher);
int		check_meal_num(t_philo *sopher);
// int		check_appetite(t_omni *data);
// int		check_death(t_omni *data);
//life.c
// void    eating(t_philo  *sophie);
// void	sleeping(t_philo *sopher);
// void	thinking(t_philo *sopher);
// void	life(t_philo *sopher);
int		philogenesis(t_omni *data);
//monitoring.c
// int		who_died(t_omni *data);
// int		who_ate(t_omni *data);
void	*monitoring(void *data);

#endif
