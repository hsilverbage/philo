/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:52:42 by henrik            #+#    #+#             */
/*   Updated: 2023/08/28 12:08:09 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_timer()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_message(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->message);
	printf("%lu\t%d %s\n", (ft_get_timer() - philo->start), philo->index, action);
	pthread_mutex_unlock(philo->message);
}

void	ft_sleep(t_philo *philo)
{
	int	wake_time;
	int	death_time;

	wake_time = (ft_get_timer() - philo->last_meal) + philo->time_to_sleep;
	death_time = (ft_get_timer() - philo->last_meal) + philo->time_to_die;
	//check_death(philo);
	if (wake_time >= death_time)
		usleep((philo->time_to_die * 1000));
	else
		usleep((philo->time_to_sleep * 1000));
	//check_death(philo);
	ft_print_message(philo, "is sleeping");
	ft_print_message(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	//need to check death
	pthread_mutex_lock(philo->left_fork);
	ft_print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print_message(philo, "has taken a fork");
	ft_print_message(philo, "is eating");
	philo->last_meal = ft_get_timer();
	usleep(philo->time_to_eat);
	philo->nb_eat += 1;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 1)
		usleep((philo->time_to_eat / 2));
	//just to cut the while loop
	philo->max_eat = 2;
	while (1)
	{
		ft_eat(philo);
		if (philo->nb_eat == philo->max_eat)
			break ;
		ft_sleep(philo);
	}
	return (NULL);
}
void	ft_init_philo(t_data *data, int i)
{
	data->philo[i].index = i + 1;
	data->philo[i].time_to_die = data->time_to_die;
	data->philo[i].time_to_eat = data->time_to_eat;
	data->philo[i].time_to_sleep = data->time_to_sleep;
	data->philo[i].max_eat = data->max_eat;
	data->philo[i].nb_eat = 0;
	data->philo[i].right_fork = &data->forks[i];
	data->philo[i].message = &data->message;
	data->philo[i].start = data->start;
}
void	ft_init_forks(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		//printf("ID PHILO IS EVEN\n i is worth %d\n ((i + 1) modulo nb_philo) = %d\n\n\n", i, ((i + 1) % data->nb_philo) );
	}
	else
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1)% data->nb_philo];
		//printf("ID PHILO IS ODD\n i is worth %d\n ((i + 1) modulo nb_philo) = %d\n\n\n", i, ((i + 1) % data->nb_philo) );
	}
}

void	ft_philo(t_data *data)
{
	unsigned long	start;
	int				i;

	i = 0;
	start = ft_get_timer();
	data->start = start;
	while (i < data->nb_philo)
	{
		ft_init_philo(data, i);
		ft_init_forks(data, i);
		pthread_create(&(data->th[i]), NULL, routine, &(data->philo[i]));
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_parsing_args(argc);
	ft_init_data(argc, argv, &data);
	ft_init_mutex(&data);
	ft_philo(&data);
	ft_join_thread(&data);
	ft_destroy_thread(&data);
	ft_free_data(&data);
	return (0);
}
