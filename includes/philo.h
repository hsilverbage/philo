#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*message;
	long long		start;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		last_meal;
	int				index;
	int				nb_eat;
	int				max_eat;
	int				*death;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_t		*th;
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_eat;
	int				death;
	t_philo			*philo;
}				t_data;

void		ft_parsing_args(int argc);
void		ft_init_data(int argc, char **argv, t_data *data);

void		ft_error(char *str);
void		ft_init_mutex(t_data *data);

void		ft_destroy_thread(t_data *data);
void		ft_join_thread(t_data *data);
void		ft_free_data(t_data *data);

void		*routine(void *arg);
void		ft_check_death(t_data *data);
long long	ft_get_timer(void);

#endif
