/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:39:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 12:51:51 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_left_to_right(t_philo *philosopher, t_data *data)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	pthread_mutex_lock(philosopher->right_fork);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
}

void	grab_right_to_left(t_philo *philosopher, t_data *data)
{
	pthread_mutex_lock(philosopher->right_fork);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
	pthread_mutex_lock(philosopher->left_fork);
	print_timestamp_ms(data, philosopher->number, MSG_TAKE);
}

void	grab_forks(t_philo *philosopher, t_data *data)
{
	if (is_even(philosopher->number) == TRUE)
		grab_left_to_right(philosopher, data);
	else
		grab_right_to_left(philosopher, data);
}

void	put_down_forks(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}
