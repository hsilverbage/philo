/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:09:39 by henrik            #+#    #+#             */
/*   Updated: 2023/09/15 12:30:14 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->message);
	if (*(philo->death) != 1)
		printf("%lld\t%d %s\n", (ft_get_timer() - *(philo->start)), \
			philo->index, s);
	pthread_mutex_unlock(philo->message);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	ft_print_message(philo, "is thinking");
	if (philo->nb_philo % 2 == 1)
		ft_usleep(5);
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
	philo->nb_eat += 1;
	pthread_mutex_unlock(philo->message);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_wait_all_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->message);
	if (philo->index == 1)
	{
		ft_usleep(philo->nb_philo);
		*(philo->start) = ft_get_timer();
	}
	pthread_mutex_unlock(philo->message);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_wait_all_philo(philo);
	if (philo->index % 2 == 0)
		ft_sleep(philo);
	while (1)
	{
		pthread_mutex_lock(philo->message);
		if (*(philo->death))
		{
			pthread_mutex_unlock(philo->message);
			break ;
		}
		pthread_mutex_unlock(philo->message);
		ft_eat(philo);
		if (philo->nb_eat == philo->max_eat)
			break ;
		ft_sleep(philo);
	}
	return (NULL);
}
