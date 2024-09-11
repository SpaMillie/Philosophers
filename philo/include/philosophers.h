/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:04:10 by mspasic           #+#    #+#             */
/*   Updated: 2024/09/11 12:36:36 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_moni
{
	int				philo_num;
	int				meal_num;
	int				stop;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	timing;
	pthread_mutex_t	start;
	pthread_mutex_t	print;
}	t_moni;

typedef struct s_philo
{
	int				id;
	int				philo_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meal_num;
	int				cur_meal;
	int				dead;
	int				*stop;
	size_t			start_time;
	size_t			last_ate;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*timing;
	pthread_mutex_t	*start;
	pthread_mutex_t	*print;
	pthread_mutex_t	state;
	pthread_mutex_t	meal_lock;
}	t_philo;

typedef struct s_omni
{
	t_moni			*tor;
	t_philo			*sophies;
}	t_omni;

/*	ALL (NON-STATIC) FUNCTIONS	*/
//handle_args.c
int		digit_finder(char *str);
int		check_args(t_moni *tor, char **argv, int argc);
//ft_atoi.c
int		ft_atoi(const char *str);
//timing.c
void	ft_usleep(t_philo *sopher, size_t sleep_time, size_t start);
size_t	get_time(void);
size_t	lock_time(pthread_mutex_t *cur);
void	change_stop(t_philo *sopher);
//utils.c
void	void_malloc_failed(t_moni *tor);
void	init_failed(t_moni *tor, t_philo *sphs, pthread_mutex_t *frks, int i);
void	cleanup(t_moni *tor, t_philo *sophies, pthread_mutex_t *forks);
size_t	print_out(char *str, t_philo *sopher);
//utils2.c
void	change_state(t_philo *sopher);
int		sudden_death(t_philo *sopher, int eat_sleep);
void	sim_cleanup(t_moni *tor, t_philo *sphs);
int		table_4_1(t_philo *sopher);
int		assassin(t_philo *sopher, int eat_print);
//checks.c
int		mutex_initing(t_philo *sophy);
int		check_state(t_philo *sopher);
int		check_stop(t_philo *sopher);
//life.c
int		philogenesis(t_omni *data);
//monitoring.c
void	*monitoring(void *data);

#endif
