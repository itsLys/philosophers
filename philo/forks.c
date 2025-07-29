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

int	grab_left_to_right(t_philo *philo, t_data *data)
{
	lock_fork(philo->left_fork, data);
	print_timestamp_ms(data, philo->number, MSG_TAKE);
	lock_fork(philo->right_fork, data);
	print_timestamp_ms(data, philo->number, MSG_TAKE);
	return (SUCCESS);
}

int	grab_right_to_left(t_philo *philo, t_data *data)
{
	lock_fork(philo->right_fork, data);
	print_timestamp_ms(data, philo->number, MSG_TAKE);
	lock_fork(philo->left_fork, data);
	print_timestamp_ms(data, philo->number, MSG_TAKE);
	return (SUCCESS);
}

int	grab_forks(t_philo *philo, t_data *data)
{
	int	status;

	status = SUCCESS;
	if (read_state(philo, data) == IS_DEAD || should_stop(0, data))
	{
		put_down_forks(philo, data);
		return (FAILURE);
	}
	if (is_even(philo->number) == TRUE)
		status = grab_left_to_right(philo, data);
	else
		status = grab_right_to_left(philo, data);
	if (status == FAILURE)
		put_down_forks(philo, data);
	return (status);
}

void	put_down_forks(t_philo *philo, t_data *data)
{
	unlock_fork(philo->right_fork, data);
	unlock_fork(philo->left_fork, data);
}
