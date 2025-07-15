/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:59:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 14:59:51 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_state(t_philo *philosopher, t_state state, char *msg, t_data *data)
{
	pthread_mutex_lock(&data->state_guard);
	philosopher->state = state;
	pthread_mutex_unlock(&data->state_guard);
	print_timestamp_ms(data, philosopher->number, msg);
}

void	update_last_meal(t_philo *philosopher, t_data *data)
{
	pthread_mutex_lock(&data->state_guard);
	philosopher->last_meal_time_ms = get_timestamp_ms(data->start_time_ms);
	pthread_mutex_unlock(&data->state_guard);
}

void	update_meal_count(t_philo *philosopher, t_data *data)
{
	pthread_mutex_lock(&data->state_guard);
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&data->state_guard);
}

