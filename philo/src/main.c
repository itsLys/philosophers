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

long	get_timestamp(t_time curr, t_time start)
{
	long	m_start_time;
	long	m_current_time;

	m_start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	m_current_time = curr.tv_sec * 1000 + curr.tv_usec / 1000;
	return m_current_time - m_start_time;
}

void print_state(t_data *data, t_philo *philo, char *msg)
{
	struct timeval	current_time;
	long			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = get_timestamp(current_time, data->start_time);
	printf("%ld %d %s", timestamp, philo->num, msg);
}

void take_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->left_philo->fork);
	print_state(data, philo, MSG_TAKE);
	pthread_mutex_lock(&philo->fork);
	print_state(data, philo, MSG_TAKE);
}

void eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_barrier);
	gettimeofday(&philo->last_meal_time, NULL);
	philo->state = EATING;
	pthread_mutex_unlock(&data->state_barrier);
	print_state(data, philo, MSG_EAT);
	usleep(data->time_to_eat * 1000);
	philo->meals_eaten++;
}

void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void ft_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_barrier);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&data->state_barrier);
	print_state(data, philo, MSG_SLEEP);
	usleep(data->time_to_sleep * 1000);
}

void think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_barrier);
	philo->state = THINKING;
	pthread_mutex_unlock(&data->state_barrier);
	print_state(data, philo, MSG_THINK);
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

int	should_stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (data->philos[i].state == DEAD)
			return TRUE;
		i++;
	}
	return FALSE;
}

int	check_state(t_data *data)
{
	// int i;
	// t_time state_change_time;
	//
	// i = 0;
	// pthread_mutex_lock(&data->state_barrier);
	// while (i < data->philos_num)
	// {
	// 	if (data->philos[i].state == THINKING)
	// 	{
	// 		gettimeofday(&state_change_time, NULL);
	// 	}
	// }
}

void monitor(t_data *data)
{
	// while (should_stop(data) == FALSE)
	// {
	// 	check_state(data);
	// }
	// checks each philo's state?
	// check
}

int main(int ac, char **av)
{
	t_data *data;
	int		philos_created;

	ac--;
	if (ac != 4 && ac != 5)
		return (printf(ERR_MSG), EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (parse_args(ac, av, data) == ERROR)
		return (printf(ERR_MSG), free(data), EXIT_FAILURE);
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
