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

int	grab_left_to_right(t_philo *philosopher, t_data *data)
{
	lock_fork(philosopher->left_fork, data);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	lock_fork(philosopher->right_fork, data);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	return SUCCESS;
}

int	grab_right_to_left(t_philo *philosopher, t_data *data)
{
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

void	put_down_forks(t_philo *philosopher, t_data *data)
{
	unlock_fork(philosopher->right_fork, data);
	unlock_fork(philosopher->left_fork, data);
}
