/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:09:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/29 15:38:32 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_threads(int number, t_data *data)
{
	int	i;

	i = 0;
	while (i < number)
		pthread_detach(data->philos[i].thread);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	destroy_forks(int number, t_data *data)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (get_fork_state(data->philos[i].left_fork, data) == UNLOCKED)
			pthread_mutex_destroy(&(data->philos[i].left_fork->mutex));
		free(data->philos[i++].left_fork);
	}
}

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->state_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->simulation);
	pthread_mutex_destroy(&data->fork_state_lock);
}

void	free_resources(t_data *data)
{
	join_threads(data);
	destroy_forks(data->number_of_philos, data);
	destroy_mutexes(data);
	free(data->args);
	free(data->philos);
}
