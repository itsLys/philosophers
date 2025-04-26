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

void *routine(void *arg)
{
	printf("philosopher number:	%d\n", ((t_data *) arg)->philos);
	return NULL;
}

void	free_resources(int num, t_data *data)
{
	int	i;

	i = 0;
	while (i < num)
		pthread_detach(data->philos[i++].philo);
	free(data->philos);
}

int init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(data->philos_num * sizeof(t_philo));
	if (data->philos == NULL)
		return (ERROR);
	i = 0;
	while (i < data->philos_num)
	{
		data->philos[i].philo_num = i;
		data->philos[i].state = THINKING;
		if (pthread_create(&data->philos[i].philo, NULL, &routine, data))
			return (i + 1);
		i++;
	}
	return (i);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_join(data->philos[i++].philo, NULL))
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
	philos_created = init_philo(data);
	if (philos_created < data->philos_num)
		return (free_resources(philos_created, data), EXIT_FAILURE);
	if (join_threads(data))
		return (free_resources(data->philos_num, data), EXIT_FAILURE);
	printf("number of philos:	%d\n", data->philos_num);
	printf("time to die:		%d\n", data->time_to_die);
	printf("time to eat:		%d\n", data->time_to_eat);
	printf("time to sleep:		%d\n", data->time_to_sleep);
	printf("meal count:		%d\n", data->meal_count);
}


// processes vs threads
// threads work on the same process
// when forking, we're working on basically different memory spaces
// while in threads we're working on the same memory spaces
//
// mutexes
//
