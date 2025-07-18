/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:09:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 10:06:40 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_threads(int number, t_data *data)
{
	int	i;

	i = 0;
	while (i < number)
		pthread_detach(data->philosophers[i].thread);
}

void	destroy_forks(int number, t_data *data)
{
	int	i;

	i = 0;
	while (i < number)
	{
		pthread_mutex_destroy(data->philosophers[i].left_fork);
		free(data->philosophers[i++].left_fork);
	}
}

int	join_threads(t_data *data)
{
	int i;

	i = 0;
	dprintf(2, "freeing resources\n");
	while (i < data->number_of_philos)
	{
		// pthread_mutex_lock(&data->state_guard);
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (ERROR);
		// pthread_mutex_unlock(&data->state_guard);
		i++;
	}
	return (SUCCESS);
}

void	free_resources(t_data *data)
{
	// pthread_mutex_lock(&data->state_guard);
	join_threads(data);
	// pthread_mutex_unlock(&data->state_guard);
	destroy_forks(data->number_of_philos, data);
	pthread_mutex_destroy(&data->print_guard);
	pthread_mutex_destroy(&data->state_guard);
	pthread_mutex_destroy(&data->simulation);
	free(data->args);
	free(data->philosophers);
}

