/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:52:42 by henrik            #+#    #+#             */
/*   Updated: 2023/09/08 18:54:00 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_timer(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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
	data->philo[i].start = &data->start;
	data->philo[i].last_meal = ft_get_timer();
	data->philo[i].nb_philo = data->nb_philo;
}

void	ft_init_forks(t_data *data, int i)
{
	if ((data->philo[i].index % 2) == 0)
	{
		data->philo[i].left_fork = &data->forks[i];
		if (data->philo[i].index != (i + 1))
			data->philo[i].right_fork = &data->forks[(i + 1)];
		else
			data->philo[i].left_fork = &data->forks[0];
		printf("EVEN : philo %d : lf is %d rf is %d\n", data->philo[i].index, i, i + 1);
	}
	else
	{
		data->philo[i].right_fork = &data->forks[i];
		if (data->philo[i].index != i + 1)
			data->philo[i].left_fork = &data->forks[i + 1];
		else
			data->philo[i].left_fork = &data->forks[0];
		printf("ODD : philo %d : lf is %d rf is %d\n", data->philo[i].index, i + 1, i);
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
	usleep(data->nb_philo * data->time_to_eat);
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
