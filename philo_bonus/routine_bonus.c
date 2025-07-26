/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:50:00 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/26 12:19:41 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_eat(t_philo *philosopher, t_data *data)
{
	grab_forks(data);
	update_state(philosopher, IS_EATING, MSG_EAT, data);
	philosopher->last_meal_time_ms = get_timestamp_ms(data->start_time_ms);
	philosopher->meals_eaten++;
	ft_sleep(data->time_to_eat, data);
	put_down_forks(data);
	return SUCCESS;
}

static int ph_sleep(t_philo *philosopher, t_data *data)
{
	update_state(philosopher, IS_SLEEPING, MSG_SLEEP, data);
	ft_sleep(data->time_to_sleep, data);
	return SUCCESS;
}

static int ph_think(t_philo *philosopher, t_data *data)
{
	update_state(philosopher, IS_THINKING, MSG_THINK, data);
	dprintf(2, "to die:			%d\n", data->time_to_die);
	dprintf(2, "time stamp:		%ld\n", get_timestamp_ms(data->start_time_ms));
	dprintf(2, "last meal:		%ld\n", philosopher->last_meal_time_ms);
	usleep(data->time_to_die - (get_timestamp_ms(data->start_time_ms) - philosopher->last_meal_time_ms));
	return (SUCCESS);
}

int	is_starving(t_philo *philo, t_data *data)
{
	if (get_timestamp_ms(data->start_time_ms)
			- philo->last_meal_time_ms
			> data->time_to_die)
		return TRUE;
	return FALSE;
}

void routine(t_philo *philosopher, t_data *data)
{
	if (data->number_of_philos == 1)
		usleep((data->time_to_die + 10) * 1000);
	while (1)
	{
		if (dprintf(2, "if state\n") && is_starving(philosopher, data))
		{
			dprintf(2, "dead\n");
			update_state(philosopher, IS_DEAD, MSG_DIED, data);
			sem_post(data->dead_philosophers);
			break;
		}
		ph_eat(philosopher, data);
		ph_sleep(philosopher, data);
		ph_think(philosopher, data);
	}
}

