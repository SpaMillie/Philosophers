/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:07:07 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/27 17:41:57 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

// int	int_malloc_failed(void)
// {
// 	printf("Error: Malloc failed.\n");
// 	return (-1);
// }



void	set_philo(t_philo *frm, t_philo *sophy, int i, pthread_mutex_t **fork)
{
	sophy->philo_num = i; //dnt forget that this isnt total philo_num
	sophy->right_fork = fork[i];
	if (i == frm->philo_num - 1)
		sophy->left_fork = fork[0];
	else
		sophy->left_fork = fork[i + 1];
	sophy->meal_num = frm->meal_num;
	sophy->time_to_sleep = frm->time_to_sleep;
	sophy->time_to_die = frm->time_to_die;
	sophy->time_to_eat = frm->time_to_eat;
	sophy->start_time = frm->start_time;
	sophy->printing = frm->printing;
	sophy->eating = frm->eating;
	sophy->dead = 0;
	if (pthread_mutex_init(&sophy->eating, NULL) != 0)
	//apply this to mutex_initing and add a check to see if you need to destroy all mutexes and free stuff
	{
		printf("Error: initialisation failed.\n");
		if (destroy_mut(&sophy->eating) != 0)
			return ;
	}
	// printf("checking %d, %d, %d\n", sophy->time_to_die, sophy->time_to_eat, sophy->time_to_sleep);
}

int	set_forks(t_philo *forum, t_philo **sophies, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < forum->philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (init_failed(*sophies, &forks, i));
	}
	return (0);
}
void	ft_print(char *str, t_philo *cur_ph, int i)
{
	size_t	cur_time;

	cur_time = get_time();
	pthread_mutex_lock(&cur_ph->printing);
	printf("%lu philosopher %d %s\n", cur_time - cur_ph->start_time, 
		cur_ph->philo_num, str);
	pthread_mutex_unlock(&cur_ph->printing);
}

void	death_ensues(t_philo **sophies, int i, int max)
{
	int	j;

	j = -1;
	ft_print("died", sophies[i], i);
	while (++j < max)
		sophies[j]->dead = 1;
}

int	check_appetite(t_omni *data)
{
	int	i;

	i = 0;
	if (data->forum->meal_num == -2)
		return (0);
	while (i < data->forum->philo_num)
	{
		if (data->sophies[i]->meal_num)
			return (0);
		i++;
	}
	return (1);
}

int	check_death(t_omni *data)
{
	int	i;

	i = 0;
	while (i < data->forum->philo_num)
	{
		pthread_mutex_lock(&data->sophies[i]->eating);
		if (data->sophies[i]->dead == 1)
		{
			death_ensues(data->sophies, i, \
				data->forum->philo_num);
			return (1) ;
		}
		pthread_mutex_lock(&data->sophies[i]->eating);
		i++;
	}
	return (0);
}

int	edo(t_philo *sopher)
{

}

void	eat_first(t_philo *sopher)
{
	while (!sopher->dead || sopher->meal_num)
	{
		if (edo(sopher))
			break ;
		if (cogito(sopher))
			break ;
		if (dormio(sopher))
			break ;
	}
}

void	think_first(t_philo *sopher)
{
	while (!sopher->dead || sopher->meal_num)
	{
		if (cogito(sopher))
			break ;
		if (edo(sopher))
			break ;
		if (dormio(sopher))
			break ;
	}
}

void	order_up(t_philo *sopher)
{
	if (sopher->philo_num == 0 || sopher->philo_num %2 == 0)
		eat_first(sopher);
	else
		think_first(sopher);
}

int	philogenesis(t_omni *data)
{
	int	i;

	i = -1;
	while (++i < data->forum->philo_num)
	{
		if (pthread_create(&data->sophies[i]->thread, NULL, \
			&order_up, data->sophies[i]) != 0)
		{
			printf("Error: philogenesis failed\n");
			while (--i > -1)
				pthread_join(data->sophies[i], NULL);
			return (1);
		}
		return (0);
	}
}

void	monitoring(t_omni *data)
{
	int	check;

	check = philogenesis(data);
	if (check != 0)
		return (genesis_error(data, check));
	while (1)
	{
		if (check_death(data))
			break ;
		if (check_appetite(data));
			break ;
	}
	//unlock everything, change flags, destroy mutexes 
	// check = -1;
	// while (++check < data->forum->philo_num)
	// 	pthread_join(data->sophies[check], NULL);
}

void	create_threads()
{}

void	start_simulation(t_philo *frm, t_philo **sphs, pthread_mutex_t **frk)
{
	t_omni	data;
	int		i;

	i = -1;
	data.forum = frm;
	data.sophies = sphs;
	data.forks = frk;
	if (pthread_create(&frm->thread, NULL, &monitoring, &data) != 0)
		printf("Error: failed to create the monitoring thread\n");
	else
		create_threads(&data, frm, sphs, frk);	
	while (++i < data.forum->philo_num)
		pthread_join(data.sophies[i], NULL);
	//join monitoring
	i = -1;	
	while (++i > data.forum->philo_num)
	{
		if (destroy_mut(data.forks[i]) != 0)
			printf("Error: mutex %d is not destroyed\n", i);
	}
}

static void	start(t_philo *forum, char **argv, int argc)
{
	int	i;
	t_philo *sophies;
	pthread_mutex_t	*forks;

	if (check_args(forum, argv, argc) == -1)
		return ;
	sophies = malloc(sizeof(t_philo) * forum->philo_num);
	if (!sophies)
		return (void_malloc_failed());
	forks = malloc(sizeof(pthread_mutex_t) * forum->philo_num);
	if (!forks)
	{
		free (sophies);
		return(void_malloc_failed());
	}
	if (set_forks(forum, &sophies, forks) == -1)
		return ;
	i = -1;
	while (++i < forum->philo_num)
		set_philo(forum, &sophies[i], i, &forks);
	start_simulation(forum, &sophies, forks);
	free(sophies);
	free(forks);
}

int	main(int argc, char **argv)
{
	t_philo	forum;
	int	i;

	i = 1;
	forum = (t_philo){0};
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (digit_finder(argv[i]) == -1)
			{
				printf("Error: Invalid arguments. Try actual numbers.\n");
				return (0);
			}
			i++;
		}
		start(&forum, argv + 1, argc);
	}
	else
		printf("Error: Invalid number of arguments.\n");
}
