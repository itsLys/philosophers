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

#define FREE 0
#define BUSY 1

void	take_forks(t_philo *philo)
{
	if (philo->fork == FREE)
		philo->fork = BUSY;
}

void	philosophy(t_philo *philo)
{
	// take_forks(philo);
	// eat(philo);
	// put_down_forks(philo);
	// update_logs(philo);
	// philo_sleep(philo);
	// update_logs(philo);
	printf("num:		%d\n", philo->philo_num);
	printf("state:		%d\n", philo->state);
	printf("right fork:	%p\n", &philo->fork);
	printf("left fork:	%p\n", &philo->left_philo->fork);
	printf("\n\n");
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	philosophy(philo);
	return NULL;
}

void	free_resources(int flag, int num, t_data *data)
{
	int	i;

	i = 0;
	if (flag == SUCCESS)
	{
		while (i < num)
			pthread_join(data->philos[i++].philo, NULL);
	}
	else if (flag == ERROR)
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
		if (pthread_create(&data->philos[i].philo, NULL, &routine, &data->philos[i]))
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
