/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:39:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 12:10:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philo *philosopher, t_data *data)
{
	grab_forks(philosopher, data);
	update_state(philosopher, IS_EATING, MSG_EAT, data);
	update_last_meal(philosopher, data);
	update_meal_count(philosopher, data);
	ft_sleep(data->time_to_eat, data);
	put_down_forks(philosopher, data);
	return SUCCESS;
}

int ph_sleep(t_philo *philosopher, t_data *data)
{
	update_state(philosopher, IS_SLEEPING, MSG_SLEEP, data);
	ft_sleep(data->time_to_sleep, data);
	return SUCCESS;
}

int ph_think(t_philo *philosopher, t_data *data)
{
	// long	think_time;
	//
	// think_time = (data->time_to_die - (data->time_to_eat + data->time_to_sleep)) - THRESHOLD;
	update_state(philosopher, IS_THINKING, MSG_THINK, data);
	// if (think_time > 1)
	// 	usleep((think_time - 1) * 1000);
	// else
	usleep(data->time_to_die - (get_timestamp_ms(data->start_time_ms) - philosopher->last_meal_time_ms));
	return (SUCCESS);
}

void *routine(void *arg)
{
	t_data	*data;
	t_philo	*philosopher;
	(void) data;
	data = ((t_args *) arg)->data;
	philosopher = ((t_args *) arg)->philosopher;
	if (data->number_of_philos == 1)
		usleep((data->time_to_die + 10) * 1000);
	while (should_stop(FALSE, data) == 0)
	{
		ph_eat(philosopher, data);
		ph_sleep(philosopher, data);
		ph_think(philosopher, data);
	}
	return NULL;
}
