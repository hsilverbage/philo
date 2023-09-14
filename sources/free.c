/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:33:05 by henrik            #+#    #+#             */
/*   Updated: 2023/09/14 18:56:26 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_death(t_data *data, int i)
{
	long long	time;
	int			death;

	time = 0;
	if (data->philo[i].last_meal == 0)
		return ;
	pthread_mutex_lock(&data->message);
	if (ft_get_timer() - data->philo[i].last_meal > data->time_to_die)
	{
		time = (ft_get_timer() - *(data->philo[i].start));
		death = data->death;
		if (data->philo[i].nb_eat == data->max_eat)
		{
			pthread_mutex_unlock(&data->message);
			return ;
		}
		if (death != 1)
			printf("%lld\t%d died\n", time, i + 1);
		data->death = 1;
		pthread_mutex_unlock(&data->message);
	}
	pthread_mutex_unlock(&data->message);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = ft_get_timer();
	while ((ft_get_timer() - start) < time)
		usleep(150);
}

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(STDERR_FILENO, &str[i++], 1);
	exit (EXIT_FAILURE);
}

void	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->th[i], NULL);
		i++;
	}
}

void	ft_destroy_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->message);
	i = 0;
}

void	ft_free_data(t_data *data)
{
	free(data->forks);
	free(data->philo);
	free(data->th);
}
