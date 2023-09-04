/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:52:42 by henrik            #+#    #+#             */
/*   Updated: 2023/09/04 16:43:04 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_timer()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_message(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->message);
	if (*(philo->death) == 1)
	{
		pthread_mutex_unlock(philo->message);
		return ;
	}
	printf("%lld\t%d %s\n", (ft_get_timer() - philo->start), philo->index, s);
	pthread_mutex_unlock(philo->message);
}
void	ft_check_death(t_data *data)
{
	long long	time;
	int	i;

	i = 0;
	time = 0;
	while (data->death != 1)
	{
		while (i < data->nb_philo)
		{
			if ((ft_get_timer() - data->philo[i].last_meal) > data->time_to_die)
			{
				pthread_mutex_lock(data->philo->message);
				time = (ft_get_timer() -	data->philo[i].start);
				printf("%lld\t%d died\n", time, i + 1);
				pthread_mutex_unlock(data->philo->message);
				data->death = 1;
			}
			i++;
		}
		i = 0;
		if (data->philo[i].nb_eat == data->max_eat)
			return ;
	}
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	if (philo->time_to_eat > philo->time_to_sleep)
	{
		ft_print_message(philo, "is thinking");
		usleep((philo->time_to_eat - philo->time_to_sleep) * 1000);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print_message(philo, "has taken a fork");
	ft_print_message(philo, "is eating");
	philo->last_meal = ft_get_timer();
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 1)
		usleep(((philo->time_to_eat / 2) * 1000));
	while (*(philo->death) != 1)
	{
		ft_eat(philo);
		philo->nb_eat += 1;
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
	data->philo[i].message = &data->message;
	data->philo[i].death = &data->death;
	data->philo[i].start = ft_get_timer();
	data->philo[i].last_meal = ft_get_timer();
}
void	ft_init_forks(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	else
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
}

void	ft_philo(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->nb_philo)
	{
		ft_init_philo(data, i);
		ft_init_forks(data, i);
		pthread_create(&(data->th[i]), NULL, routine, &(data->philo[i]));
		i++;
	}
	usleep(data->nb_philo * 5000);
	ft_check_death(data);
	ft_join_thread(data);
	ft_destroy_thread(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_parsing_args(argc);
	ft_init_data(argc, argv, &data);
	ft_init_mutex(&data);
	ft_philo(&data);
	ft_free_data(&data);
	return (0);
}

