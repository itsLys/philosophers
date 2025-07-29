/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:52:17 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/29 16:48:03 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <fcntl.h>

# define THRESHOLD 3
# define FAILURE 1
# define ERROR -1
# define INFINITE -1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define SEM_FORKS "/forks"
# define SEM_PRINT "/print_guard"
# define SEM_DEAD_PHILOS "/dead_philos"
# define SEM_FULL_PHILOS "/full_philos"
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
}	t_state;

typedef struct s_philo
{
	pid_t			pid;
	t_state			state;
	int				meals_eaten;
	int				number;
	long			last_meal_time_ms;
	int				is_full;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print_lock;
	sem_t			*dead_philos;
	sem_t			*full_philos;
	int				should_stop;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long			start_time_ms;
}	t_data;

// monitor
int					is_starving(t_philo *philo, t_data *data);
void				track_meal_count(t_data *data);
void				monitor(t_data *data);
// init data
int					init_data(int ac, char **av, t_data *data);
int					init_philos(t_data *data);

// cleanup
void				clear_semaphores(t_data *data);
void				clean_exit(int status, t_data *data);
void				kill_children(int created, t_data *data);

//parse
int					parse_args(int ac, char **av, t_data *data);

// utils
void				*ft_malloc(size_t size);

// sleep
void				ft_sleep(long time, t_data *data);

// time
long				gettimeofday_ms(void);
long				get_timestamp_ms(long t0_ms);
long				get_time_left(t_philo *philo, t_data *data);
void				print_timestamp_ms(t_data *data,
						t_philo *philo,
						char *msg);

// update
void				update_state(t_philo *philo,
						t_state state,
						char *msg,
						t_data *data);

// fork
void				grab_forks(t_philo *philo, t_data *data);

void				put_down_forks(t_data *data);

// routine
void				routine(t_philo *philo, t_data *data);

#endif // !PHILO_BONUS_H
