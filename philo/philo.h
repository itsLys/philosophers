/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:52:17 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 12:05:53 by ihajji           ###   ########.fr       */
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

# define FAILURE 1
# define ERROR -1
# define INFINITE -1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define MSG_TAKE "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_THINK "is thinking\n"
# define MSG_DIED "died\n"
# define MSG_USAGE "Usage:\n \
	./philo \
	number_of_philos \
	time_to_die \
	time_to_eat \
	time_to_sleep \
	[meal_count]\n"

typedef struct timeval	t_time;
typedef struct s_args	t_args;

typedef enum e_fork_state
{
	UNLOCKED,
	LOCKED
}	t_fork_state;

typedef enum e_state
{
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD
}						t_state;

typedef struct s_fork
{
	int				state;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_state			state;
	int				meals_eaten;
	int				number;
	long			last_meal_time_ms;
	int				is_full;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation;
	pthread_mutex_t	fork_state_lock;
	int				should_stop;
	t_philo			*philos;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long			start_time_ms;
	t_args			*args;
}	t_data;

struct s_args
{
	t_data			*data;
	t_philo			*philo;
};

// uncategorized
void				*routine(void *arg);

// init
int					init_data(int ac, char **av, t_data *data);
int					init_philos(t_data *data);
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
long				get_time_left(t_philo *philo, t_data *data);

// cleanup
void				free_resources(t_data *data);
int					join_threads(t_data *data);
void				destroy_forks(int number, t_data *data);
void				detach_threads(int number, t_data *data);
void				destroy_mutexes(t_data *data);

// forks
int					grab_left_to_right(t_philo *philo, t_data *data);
int					grab_right_to_left(t_philo *philo, t_data *data);
int					grab_forks(t_philo *philo, t_data *data);
void				put_down_forks(t_philo *philo, t_data *data);

// fork_utils
t_fork_state		get_fork_state(t_fork *fork, t_data *data);
void				lock_fork(t_fork *fork, t_data *data);
void				unlock_fork(t_fork *fork, t_data *data);

// routine
int					ph_eat(t_philo *philo, t_data *data);
int					ph_sleep(t_philo *philo, t_data *data);
int					ph_think(t_philo *philo, t_data *data);
void				*routine(void *arg);

// update
void				update_last_meal(t_philo *philo, t_data *data);
void				update_meal_count(t_philo *philo, t_data *data);
t_state				read_state(t_philo *philo, t_data *data);
int					should_stop(int set, t_data *data);
void				update_state(t_philo *philo,
						t_state state,
						char *msg,
						t_data *data);

// monitor
void				monitor(t_data *data);
int					should_stop(int set, t_data *data);

// monitor utils
int					is_starving(t_philo *philo, t_data *data);
int					is_full(t_philo *philo, t_data *data);

#endif // !PHILO_H
