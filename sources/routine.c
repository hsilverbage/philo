/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:09:39 by henrik            #+#    #+#             */
/*   Updated: 2023/09/06 11:31:10 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			pthread_mutex_lock(data->philo->message);
			if (ft_get_timer() - data->philo[i].last_meal > data->time_to_die)
			{
				time = (ft_get_timer() - data->philo[i].start);
				if (data->philo[i].nb_eat != data->max_eat)
					printf("%lld\t%d died\n", time, i + 1);
				data->death = 1;
			}
			pthread_mutex_unlock(data->philo->message);
			i++;
		}
		pthread_mutex_lock(data->philo->message);
		if (data->philo[i].nb_eat == data->max_eat)
			return ;
		pthread_mutex_unlock(data->philo->message);
		i = 0;
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
	pthread_mutex_lock(philo->message);
	philo->last_meal = ft_get_timer();
	pthread_mutex_unlock(philo->message);
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
		pthread_mutex_lock(philo->message);
		philo->nb_eat += 1;
		pthread_mutex_unlock(philo->message);
		if (philo->nb_eat == philo->max_eat)
			break ;
		ft_sleep(philo);
	}
	return (NULL);
}
