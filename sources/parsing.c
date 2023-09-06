/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrik <henrik@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:48:09 by henrik            #+#    #+#             */
/*   Updated: 2023/09/04 16:43:30 by henrik           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t		i;
	long int	result;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r' \
			|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		if (result != ((result * 10 + (str[i] - '0')) / 10))
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			ft_error("Error : mutex initialization\n");
		i++;
	}
	if (pthread_mutex_init(&data->message, NULL) != 0)
		ft_error("Error : mutex initialization\n");
}
void	ft_one_philo(t_data *data)
{
	printf("0\t1 has taken a fork\n");
	usleep(data->time_to_die);
	printf("%lld\t1 died\n", data->time_to_die);
	exit (EXIT_SUCCESS);
}

void	ft_init_data(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = -2;
	if (data->nb_philo < 1 || data->time_to_die == -1 \
		|| data->time_to_eat == -1 || data->time_to_sleep == -1 \
		|| data->max_eat == -1 || data->nb_philo > 250)
		ft_error("Invalid argument\n");
	if (data->nb_philo == 1)
		ft_one_philo(data);
	data->death = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->th = malloc(sizeof(pthread_t) * data->nb_philo);
}

void	ft_parsing_args(int argc)
{
	if (argc < 5 || argc > 6)
		ft_error("Wrong number of arguments\n");
}

