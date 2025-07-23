/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:48:13 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 10:48:34 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philo *philo, t_data *data)
{
	int	is_full;

	pthread_mutex_lock(&data->state_lock);
	is_full = philo->is_full;
	pthread_mutex_unlock(&data->state_lock);
	return is_full;
}

int	is_starving(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	if (get_timestamp_ms(data->start_time_ms)
			- philo->last_meal_time_ms
			> data->time_to_die)
	{
		pthread_mutex_unlock(&data->state_lock);
		return TRUE;
	}
	pthread_mutex_unlock(&data->state_lock);
	return FALSE;
}
