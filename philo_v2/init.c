/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/01 11:39:07 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	t_fork *left_fork;
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		left_fork = malloc(sizeof(t_fork));
		if (left_fork == NULL || pthread_mutex_init(left_fork, NULL))
			return free(left_fork), i;
		data->philosophers[i].left_fork = left_fork;
		if (i > 0)
			data->philosophers[i].right_fork =
				data->philosophers[i - 1].left_fork;
		i++;
	}
	data->philosophers[0].right_fork = data->philosophers[i - 1].left_fork;
	return (i);
} // WARN: ptrs must be freeed by the end of the program

int init_philosophers(t_data *data)
{
	int		i;

	data->args = malloc(data->number_of_philos * sizeof(t_args));
	if (data->args == NULL)
		return (ERROR);
	i = 0;
	while (i < data->number_of_philos)
	{
		data->args[i] = (t_args) {data, data->philosophers + i} ;
		data->philosophers[i].number = i + 1;
		if (pthread_create(&data->philosophers[i].thread, NULL, &routine, data->args + i))
			return i;
		i++;
	}
	return (i);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (parse_args(ac, av, data) == ERROR)
		return (ERROR);
	// init variables
	data->start_time_ms = gettimeofday_ms();
	data->should_stop = FALSE;
	// init_mutexes
	if (pthread_mutex_init(&data->state_guard, NULL))
		return (ERROR);
	if (pthread_mutex_init(&data->print_guard, NULL))
		return (pthread_mutex_destroy(&data->state_guard), ERROR);
	if (pthread_mutex_init(&data->simulation, NULL))
		return (pthread_mutex_destroy(&data->state_guard),
				pthread_mutex_destroy(&data->print_guard),
				ERROR);
	// init_philosophers
	data->philosophers = ft_malloc(data->number_of_philos * sizeof(t_philo));
	if (data->philosophers == NULL)
		return (pthread_mutex_destroy(&data->state_guard),
				pthread_mutex_destroy(&data->print_guard),
				pthread_mutex_init(&data->simulation, NULL),
				ERROR);
	return (EXIT_SUCCESS);
}
