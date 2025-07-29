/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:59:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 18:58:01 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_state	read_state(t_philo *philo, t_data *data)
{
	t_state	state;

	pthread_mutex_lock(&data->state_lock);
	state = philo->state;
	pthread_mutex_unlock(&data->state_lock);
	return (state);
}

void	update_state(t_philo *philo, t_state state, char *msg, t_data *data)
{
	if (should_stop(FALSE, data))
		return ;
	pthread_mutex_lock(&data->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&data->state_lock);
	print_timestamp_ms(data, philo->number, msg);
}

void	update_last_meal(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	philo->last_meal_time_ms = get_timestamp_ms(data->start_time_ms);
	pthread_mutex_unlock(&data->state_lock);
}

void	update_meal_count(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten >= data->meal_count)
		philo->is_full = TRUE;
	pthread_mutex_unlock(&data->state_lock);
}
