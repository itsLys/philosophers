/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:52:17 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 14:59:48 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

# define THRESHOLD 3
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
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}	t_state;

typedef pthread_mutex_t t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_state			state;
	int				meals_eaten;
	int				number;
	long			last_meal_time_ms;
}	t_philo ;

typedef struct s_args t_args;

typedef struct s_data
{
	pthread_mutex_t state_guard;
	pthread_mutex_t print_guard;
	t_philo			*philosophers;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long			start_time_ms;
	t_args			*args;
}	t_data ;

struct s_args
{
	t_data			*data;
	t_philo			*philosopher;
};

// uncategorized
void				*routine(void *arg);

// init
int					init_data(int ac, char **av, t_data *data);
int					init_philosophers(t_data *data);
int					init_forks(t_data *data);

//parse
int					parse_args(int ac, char **av, t_data *data);

// utils
void				*ft_malloc(size_t size);
int					is_even(int n);
void				ft_sleep(long time, t_data *data);

// time
long				timeval_to_ms(struct timeval time);
long				gettimeofday_ms(void);
long				get_timestamp_ms(long t0_ms);
void				print_timestamp_ms(t_data *data, int num, char *msg);

// cleanup
void				free_resources(t_data *data);
int					join_threads(t_data *data);
void				destroy_mutexes(int number, t_data *data);
void				detach_threads(int number, t_data *data);

// forks
void				grab_left_to_right(t_philo *philosopher, t_data *data);
void				grab_right_to_left(t_philo *philosopher, t_data *data);
void				grab_forks(t_philo *philosopher, t_data *data);
void				put_down_forks(t_philo *philosopher, t_data *data);

// routine
void				update_state(t_philo *philosopher, t_state state, char *msg, t_data *data);
void				ph_eat(t_philo *philosopher, t_data *data);
void				ph_sleep(t_philo *philosopher, t_data *data);
void				ph_think(t_philo *philosopher, t_data *data);
void				*routine(void *arg);

// update
void				update_state(t_philo *philosopher, t_state state, char *msg, t_data *data);
void				update_last_meal(t_philo *philosopher, t_data *data);
void				update_meal_count(t_philo *philosopher, t_data *data);
t_state				read_state(t_philo *philosopher, t_data *data);

#endif // !PHILO_H
