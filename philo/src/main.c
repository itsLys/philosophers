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
#define FREE 0
#define BUSY 1

pthread_mutex_t m;
unsigned long x = 0;

void *routine(void *arg)
{
	pthread_mutex_lock(&m);

	while (x != (unsigned long) arg)
	{
		pthread_mutex_unlock(&m);
		pthread_mutex_lock(&m);
	}
	printf("Hello from philo %ld\n", (unsigned long) arg);
	x++;
	pthread_mutex_unlock(&m);
	return NULL;
}

void	free_resources(int flag, int num, t_data *data)
{
	int	i;

	i = 0;
	if (flag == ERROR)
	{
		while (i < num)
			pthread_detach(data->philos[i++].philo);
	}
	free(data->philos);
	free(data);
	// TODO: Find a way to detatch threads when nececcary, and join them when program is successful
	// maybe only join since both release the resourses
}

int init_philos(t_data *data)
{
	pthread_mutex_init(&m, NULL);
	int	i;

	i = -1;
	data->philos = malloc(data->philos_num * sizeof(t_philo));
	if (data->philos == NULL)
		return (ERROR);
	i = 0;
	while (i < data->philos_num)
	{
		data->philos[i].philo_num = i;
		data->philos[i].state = THINKING;
		data->philos[i].fork = FREE;
		if (i > 0)
			data->philos[i].left_philo = &data->philos[i - 1];
		else
			data->philos[i].left_philo = &data->philos[data->philos_num - 1];
		if (pthread_create(&data->philos[i].philo, NULL, &routine, (void *)((unsigned long) i)))
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

int main(int ac, char **av)
{
	t_data *data;
	int		philos_created;

	ac--;
	if (ac != 4 && ac != 5)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (parse_args(ac, av, data) == ERROR)
		return (free(data), EXIT_FAILURE);
	philos_created = init_philos(data);
	if (philos_created < data->philos_num)
		return (free_resources(ERROR, philos_created, data), EXIT_FAILURE);
	if (join_threads(data))
		return (free_resources(ERROR, data->philos_num, data), EXIT_FAILURE);
	free_resources(SUCCESS, 0, data);
	return SUCCESS;
}

// processes vs threads
// threads work on the same process
// when forking, we're working on basically different memory spaces
// while in threads we're working on the same memory spaces
//
// mutexes
//
