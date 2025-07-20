/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:39:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 19:09:39 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// lock the mutex and set the flag to locked

void	lock_fork(t_fork *fork, t_data *data)
{
	pthread_mutex_lock(&data->fork_state_lock);
	pthread_mutex_lock(&fork->mutex);
	fork->state = LOCKED;
	pthread_mutex_unlock(&data->fork_state_lock);
}

int	grab_left_to_right(t_philo *philosopher, t_data *data)
{
	if (read_state(philosopher, data) == IS_DEAD || should_stop(0, data))
		return FAILURE;
	lock_fork(philosopher->left_fork, data);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	lock_fork(philosopher->right_fork, data);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	return SUCCESS;
}

int	grab_right_to_left(t_philo *philosopher, t_data *data)
{
	if(read_state(philosopher, data) == IS_DEAD || should_stop(0, data))
		return FAILURE;
	lock_fork(philosopher->right_fork, data);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	lock_fork(philosopher->left_fork, data);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	return SUCCESS;
}

int		grab_forks(t_philo *philosopher, t_data *data)
{
	int	status;

	status = SUCCESS;
	if (read_state(philosopher, data) == IS_DEAD || should_stop(0, data))
	{
		put_down_forks(philosopher, data);;
		return FAILURE;
	}
	if (is_even(philosopher->number) == TRUE)
		status = grab_left_to_right(philosopher, data);
	else
		status = grab_right_to_left(philosopher, data);
	if (status == FAILURE)
		put_down_forks(philosopher, data);
	return status;
}

void	drop_fork(t_fork *fork, t_data *data)
{
	pthread_mutex_lock(&data->fork_state_lock);
	if (fork->state == LOCKED)
		pthread_mutex_unlock(&fork->mutex);
	pthread_mutex_unlock(&data->fork_state_lock);
}

void	put_down_forks(t_philo *philosopher, t_data *data)
{
	drop_fork(philosopher->right_fork, data);
	drop_fork(philosopher->left_fork, data);
	// pthread_mutex_unlock(philosopher->right_fork);
	// pthread_mutex_unlock(philosopher->left_fork);
}
// NOTE: make a flag that entails the forks are locked, because when returning from update state
// it is still holding mutex forks,
// make a flag, if it is locked, unlock it
// Allahoma yassir
