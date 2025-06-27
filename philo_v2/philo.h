/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:52:17 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/27 20:31:10 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define ERROR -1
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
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}	t_state;

typedef struct s_philo
{
	pthread_mutex_t	right_fork;
	pthread_mutex_t left_fork;
	pthread_t		thread;
	t_state			state;
	int				meals_eaten;
	int				number;
	long			last_meal_time_ms;
}	t_philo ;

typedef struct s_data
{
	pthread_mutex_t state_guard;
	pthread_mutex_t print_guard;
	t_philo			*philsophers;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long			start_time_ms;
} t_data ;

// utils
void	*ft_malloc(size_t size);

#endif // !PHILO_H
