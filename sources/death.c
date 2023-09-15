/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:22:31 by henrik            #+#    #+#             */
/*   Updated: 2023/09/15 12:24:39 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_death(t_data *data, int i)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(&data->message);
	if (data->philo[i].last_meal == 0 || data->philo[i].nb_eat == data->max_eat)
	{
		pthread_mutex_unlock(&data->message);
		return ;
	}
	pthread_mutex_unlock(&data->message);
	pthread_mutex_lock(&data->message);
	if (ft_get_timer() - data->philo[i].last_meal > data->time_to_die)
	{
		time = (ft_get_timer() - *(data->philo[i].start));
		if (data->death != 1)
			printf("%lld\t%d died\n", time, i + 1);
		data->death = 1;
	}
	pthread_mutex_unlock(&data->message);
}

void	ft_check_death(t_data *data)
{
	int			i;

	i = 0;
	while (data->death != 1)
	{
		while (i < data->nb_philo)
		{
			ft_print_death(data, i);
			pthread_mutex_lock(data->philo->message);
			if (data->philo[i].nb_eat == data->max_eat)
			{
				pthread_mutex_unlock(data->philo->message);
				return ;
			}
			pthread_mutex_unlock(data->philo->message);
			i++;
		}
		i = 0;
	}
}
