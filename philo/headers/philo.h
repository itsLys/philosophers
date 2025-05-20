/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:20:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/04/17 16:39:54 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

# define ERROR -1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define MSG_TAKE "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_THINK "is thinking\n"
# define MSG_DIED "died\n"
# define MSG_USAGE "Usage:\n \
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meal_count]\n"

typedef struct timeval t_time;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;


typedef struct s_philo
{
	pthread_t		philo;
	int				num;
	t_state			state;
	pthread_mutex_t	fork;
	struct s_philo	*left_philo;
	int				meals_eaten;
	t_time			last_meal_time;
}	t_philo ;

typedef struct s_data
{
	t_philo			*philos;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	t_time			start_time;
	pthread_mutex_t state_barrier;
}	t_data ;

typedef struct	s_args
{
	t_data	*data;
	t_philo	*philo;
}	t_args;

int	parse_num(char *str);
int	parse_args(int ac, char **av, t_data *data);
#endif // !PHILO_H
