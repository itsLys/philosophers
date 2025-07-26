/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:32:56 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 19:11:59 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork_state	get_fork_state(t_fork *fork, t_data *data)
{
	t_fork_state state;

	pthread_mutex_lock(&data->fork_state_lock);
	state = fork->state;
	pthread_mutex_unlock(&data->fork_state_lock);
	return state;
}

void	lock_fork(t_fork *fork, t_data *data)
{
	pthread_mutex_lock(&fork->mutex);
	pthread_mutex_lock(&data->fork_state_lock);
	dprintf(2, "locked fork: %p\n", fork);
	fork->state = LOCKED;
	pthread_mutex_unlock(&data->fork_state_lock);
}

void	unlock_fork(t_fork *fork, t_data *data)
{
	// dprintf(2, "unlocked fork: %p\n", fork);
	pthread_mutex_lock(&data->fork_state_lock);
	if (fork->state == LOCKED && dprintf(2, "unlocked fork: %p\n", fork))
	{
		fork->state = UNLOCKED;
		pthread_mutex_unlock(&fork->mutex);
	}
	pthread_mutex_unlock(&data->fork_state_lock);
}
