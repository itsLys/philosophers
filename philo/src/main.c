/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:18:46 by ihajji            #+#    #+#             */
/*   Updated: 2025/04/17 16:39:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <unistd.h>

void	free_resources(int num, t_data *data)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(data->philos[i].philo, NULL);
		pthread_mutex_destroy(&data->philos[i++].fork);
	}
	pthread_mutex_destroy(&data->state_guard);
	free(data->philos);
	free(data);
}

long	timeval_to_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	gettimeofday_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (timeval_to_ms(time));
}

long	get_timestamp_ms(long t0_ms)
{
	return (gettimeofday_ms() - t0_ms);
}

// TODO: data->should_stop  is not locked properly.
// Make a function to get the state in a thread safe way.
// Because it is the cause of all the errors from hellgrind.
void print_timestamp_ms(t_data *data, int num, char *msg)
{
	long	timestamp;

	if (data->should_stop == TRUE && strcmp(msg, MSG_DIED))
		return ;
	timestamp = get_timestamp_ms(data->t0_ms);
	pthread_mutex_lock(&data->output_guard);
	printf("%ld %d %s", timestamp, num, msg);
	pthread_mutex_unlock(&data->output_guard);
}

void take_forks(t_data *data, t_philo *philo)
{
	if  (philo->num % 2 == 0)
		pthread_mutex_lock(&philo->fork);
	else
		pthread_mutex_lock(&philo->left_philo->fork);
	print_timestamp_ms(data, philo->num, MSG_TAKE);
	if (philo->num % 2 == 0)
		pthread_mutex_lock(&philo->left_philo->fork);
	else
		pthread_mutex_lock(&philo->fork);
	print_timestamp_ms(data, philo->num, MSG_TAKE);
}

void eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_guard);
	philo->last_meal_time_ms = gettimeofday_ms();
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&data->state_guard);
		return ;
	}
	philo->state = EATING;
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp_ms(data, philo->num, MSG_EAT);
	usleep(data->time_to_eat * 1000);
}

void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left_philo->fork);
}

void ft_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_guard);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&data->state_guard);
		return ;
	}
	philo->state = SLEEPING;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp_ms(data, philo->num, MSG_SLEEP);
	usleep(data->time_to_sleep * 1000);
}

void think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_guard);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&data->state_guard);
		return ;
	}
	philo->state = THINKING;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp_ms(data, philo->num, MSG_THINK);
	if (data->philos_num % 2 != 0)
		usleep((data->time_to_die - (data->time_to_sleep + data->time_to_eat)) * 1000);
}

void *routine(void *arg)
{
	t_data *data;
	t_philo *philo;

	data = ((t_args *) arg)->data;
	philo = ((t_args *) arg)->philo;
	while (data->should_stop == 0)
	{
		take_forks(data, philo);
		eat(data, philo);
		put_down_forks(philo);
		ft_sleep(data, philo);
		think(data, philo);
	}
	return NULL;
}

int init_philos(t_data *data)
{
	t_args *args;
	int		i;

	data->philos = malloc(data->philos_num * sizeof(t_philo));
	memset(data->philos, 0, data->philos_num * sizeof(t_philo));
	args = malloc(data->philos_num * sizeof(t_args)); // TODO: check malloc
	if (data->philos == NULL)
		return (ERROR);
	i = 0;
	data->philos[0].left_philo = &data->philos[data->philos_num - 1];
	while (i < data->philos_num)
	{
		args[i] = (t_args) {data, data->philos + i} ;
		data->philos[i].num = i;
		data->philos[i].state = -1;
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
			return (ERROR);
		if (i > 0)
			data->philos[i].left_philo = &data->philos[i - 1];
		if (pthread_create(&data->philos[i].philo, NULL, &routine, args + i))
			return (i + 1);
		i++;
	}
	return (i);
}

int	join_threads(t_data *data)
{
	while (data->philos_num)
	{
		if (pthread_join(data->philos[--data->philos_num].philo, NULL))
			return (ERROR);
	}
	return (SUCCESS);
}

// void	update_history(t_data *data, t_history *history)
// {
// 	int i;
//
// 	i = 0;
// 	pthread_mutex_lock(&data->state_guard);
// 	while (i < data->philos_num)
// 	{
// 		history[i].last_meal_count = data->philos[i].meals_eaten;
// 		history[i].last_meal_time_ms = data->philos[i].last_meal_time_ms;
// 		// pthread_mutex_unlock(&data->state_guard);
// 		// pthread_mutex_lock(&data->state_guard);
// 		i++;
// 	}
// 	pthread_mutex_unlock(&data->state_guard);
// }

int	check_starved(t_data *data, t_history *history)
{
	int i;
	long	time_passed;

	(void) history;
	i = 0;
	pthread_mutex_lock(&data->state_guard);
	while (i < data->philos_num)
	{
		// if (data->philos[i].meals_eaten == history[i].last_meal_count)
		// {
		if (data->philos[i].last_meal_time_ms)
			time_passed = gettimeofday_ms() - data->philos[i].last_meal_time_ms;
		else
			time_passed = gettimeofday_ms() - data->t0_ms;
		if (time_passed > data->time_to_die)
		{
			// printf("last meal time	%ld\n", history[i].last_meal_time_ms);
			// printf("time passed	%ld\n", time_passed);
			// printf("time to die	%d\n", data->time_to_die);
			data->philos[i].state = DEAD;
			pthread_mutex_unlock(&data->state_guard);
			return i;
		}
		// }
		pthread_mutex_unlock(&data->state_guard);
		pthread_mutex_lock(&data->state_guard);
		i++;
	}
	pthread_mutex_unlock(&data->state_guard);
	return -1;
}

void monitor(t_data *data)
{
	// usleep();
	t_history *meal_history;
	int			dead_philo;

	meal_history = malloc(data->philos_num * sizeof(t_history));// TODO: check malloc
	memset(meal_history, 0, data->philos_num * sizeof(t_history));
	while (1)
	{
		usleep(data->time_to_die * 1000);
		// update_history(data, meal_history);
		dead_philo = check_starved(data, meal_history);
		if (dead_philo >= 0)
		{
			// TODO: LOCK
			data->should_stop = TRUE;
			print_timestamp_ms(data, dead_philo, MSG_DIED);
			free_resources(data->philos_num, data);
			exit(0);
		}
	}
}

int main(int ac, char **av)
{
	t_data *data;
	int		philos_created;

	ac--;
	if (ac != 4 && ac != 5)
		return (printf(MSG_USAGE), EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (init_data(ac, av, data) == ERROR)
		return (printf(MSG_USAGE), free(data), EXIT_FAILURE);
	philos_created = init_philos(data);
	if (philos_created < data->philos_num)
		return (free_resources(philos_created, data), EXIT_FAILURE);
	monitor(data);
	// if (join_threads(data))
	// 	return (free_resources(data->philos_num, data), EXIT_FAILURE);
	// free_resources(0, data);
	return SUCCESS;
}

// processes vs threads
// threads work on the same process
// when forking, we're working on basically different memory spaces
// while in threads we're working on the same memory spaces
//
// mutexes
//
//
// TODO: handle one philo
