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

long	get_time_left(t_philo *philosopher, t_data *data)
{
	long	time_left;
	long	time_passed;

	time_passed = get_timestamp_ms(data->start_time_ms)
		- philosopher->last_meal_time_ms;
	time_left = data->time_to_die - time_passed;
	if (time_left > 0)
		return (time_left);
	return 0;
}

int ph_think(t_philo *philosopher, t_data *data)
{
	update_state(philosopher, IS_THINKING, MSG_THINK, data);
	ft_sleep(get_time_left(philosopher, data), data);
	// usleep();
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
