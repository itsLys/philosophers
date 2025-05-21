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
#include <unistd.h>

void	free_resources(int num, t_data *data)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_detach(data->philos[i++].philo);
		pthread_mutex_destroy(&data->philos[i].fork);
	}
	free(data->philos);
	free(data);
}

long	timeval_to_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_timestamp_ms(struct timeval t0)
{
	t_time time;

	gettimeofday(&time, NULL);
	return (timeval_to_ms(time) - timeval_to_ms(t0));
}

void print_timestamp(struct timeval t0, int num, char *msg)
{
	long	timestamp;

	timestamp = get_timestamp_ms(t0);
	printf("%ld %d %s", timestamp, num, msg);
}

void take_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->left_philo->fork);
	print_timestamp(data->t0, philo->num, MSG_TAKE);
	pthread_mutex_lock(&philo->fork);
	print_timestamp(data->t0, philo->num, MSG_TAKE);
}

void eat(t_data *data, t_philo *philo)
{
	t_time	curr;
	gettimeofday(&curr, NULL);
	pthread_mutex_lock(&data->state_guard);
	philo->last_meal_time_ms = timeval_to_ms(curr);
	philo->state = EATING;
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp(data->t0, philo->num, MSG_EAT);
	usleep(data->time_to_eat * 1000);
}

void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void ft_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_guard);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp(data->t0, philo->num, MSG_SLEEP);
	usleep(data->time_to_sleep * 1000);
}

void think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_guard);
	philo->state = THINKING;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp(data->t0, philo->num, MSG_THINK);
}

void *routine(void *arg)
{
	t_data *data;
	t_philo *philo;

	data = ((t_args *) arg)->data;
	philo = ((t_args *) arg)->philo;
	while (philo->state != DEAD)
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
	args = malloc(data->philos_num * sizeof(t_args));
	if (data->philos == NULL)
		return (ERROR);
	i = 0;
	data->philos[i].left_philo = &data->philos[data->philos_num - 1];
	while (i < data->philos_num)
	{
		args[i].data = data;
		args[i].philo = data->philos + i;
		data->philos[i].num = i;
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

int	check_state(t_data *data, int *last_meal_count)
{
	int i;
	t_time	current;
	long	current_ms;

	i = 0;
	pthread_mutex_lock(&data->state_guard);
	gettimeofday(&current, NULL);

	while (i < data->philos_num)
	{
		if (data->philos[i].state == EATING)
		{
			last_meal_count[i] = data->philos[i].meals_eaten;
		}
		i++;
	}
	
	// if state is eating
	// take last meal count;
	// and go read the value of last meal time, check if current time minus it, greater
	// then time to die    50ms, cur == 55, time to die == 10;
	// 55 - 50 == 5 > timetodie ? NO
	// if YES
	// check if the meal count is the same, NO? philo is dead
}

void monitor(t_data *data)
{
	static int	*last_meal_count;

	last_meal_count = malloc(data->philos_num);
	// TODO: check malloc
	while (1)
	{
		check_state(data, last_meal_count);
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
	if (parse_args(ac, av, data) == ERROR)
		return (printf(MSG_USAGE), free(data), EXIT_FAILURE);
	philos_created = init_philos(data);
	if (philos_created < data->philos_num)
		return (free_resources(philos_created, data), EXIT_FAILURE);
	monitor(data);
	if (join_threads(data))
		return (free_resources(data->philos_num, data), EXIT_FAILURE);
	free_resources(0, data);
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
