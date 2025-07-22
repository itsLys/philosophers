/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:09:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 19:11:56 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// t_fork_state	get_fork_state(t_fork *fork, t_data *data)
// {
// 	t_fork_state state;
//
// 	pthread_mutex_lock(&data->fork_state_lock);
// 	state = fork->state;
// 	pthread_mutex_unlock(&data->fork_state_lock);
// 	return state;
// }

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
		if (get_fork_state(data->philosophers[i].left_fork, data) == UNLOCKED)
			pthread_mutex_destroy(&(data->philosophers[i].left_fork->mutex));
		else
			dprintf(2, "%d is still holding fork: %p!!!\n",
					data->philosophers[i].number,
					data->philosophers[i].left_fork);
		free(data->philosophers[i++].left_fork);
	}
}

int	join_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philos)
	{
		// dprintf(2, "freeing resources %d\n", i);
		// pthread_mutex_lock(&data->state_guard);
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (ERROR);
		// dprintf(2, "freeing resources %d\n", i);
		// pthread_mutex_unlock(&data->state_guard);
		i++;
	}
	return (SUCCESS);
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
	// pthread_mutex_lock(&data->state_guard);
	// pthread_mutex_unlock(&data->state_guard);
	join_threads(data);
	destroy_forks(data->number_of_philos, data);
	destroy_mutexes(data);
	free(data->args);
	free(data->philosophers);
}

