/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:00:28 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 16:12:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_eat(t_philo *philosopher, t_data *data)
{
	grab_forks(philosopher, data);
	update_state(philosopher, IS_EATING, MSG_EAT, data);
	philosopher->last_meal_time_ms = get_timestamp_ms(data->start_time_ms);
	philosopher->meals_eaten++;
	if (data->meal_count != INFINITE && philosopher->meals_eaten >= data->meal_count)
	{
		philosopher->is_full = TRUE;
		sem_post(data->full_philos);
	}
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
	long time;

	update_state(philosopher, IS_THINKING, MSG_THINK, data);
	time = get_time_left(philosopher, data);
	if (time)
		ft_sleep(time, data);
	else
		usleep(500);
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
	sem_wait(data->dead_philos);
	if (data->meal_count != INFINITE)
		sem_wait(data->full_philos);
	if (data->number_of_philos == 1)
		usleep((data->time_to_die + 10) * 1000);
	if (philosopher->number % 2 == 0)
		ft_sleep(data->time_to_eat - 1, data);
	while (1)
	{
		// if (is_starving(philosopher, data))
		// {
		// 	update_state(philosopher, IS_DEAD, MSG_DIED, data);
		// 	sem_post(data->dead_philosophers);
		// 	break;
		// }
		ph_eat(philosopher, data);
		ph_sleep(philosopher, data);
		ph_think(philosopher, data);
	}
}
