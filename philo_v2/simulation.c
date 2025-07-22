/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:45:10 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 18:57:34 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_starving(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	if (get_timestamp_ms(data->start_time_ms)
			- philo->last_meal_time_ms
			>= data->time_to_die)
	{
		pthread_mutex_unlock(&data->state_lock);
		return TRUE;
	}
	pthread_mutex_unlock(&data->state_lock);
	return FALSE;
}

int	should_stop(int set, t_data *data)
{
	int	should_stop;

	if (set)
	{
		pthread_mutex_lock(&data->simulation);
		data->should_stop = TRUE;
		pthread_mutex_unlock(&data->simulation);
	}
	pthread_mutex_lock(&data->simulation);
	should_stop = data->should_stop;
	pthread_mutex_unlock(&data->simulation);
	// dprintf(2, "%d\n", should_stop);
	return (should_stop);
}
