/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:00:28 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/29 16:47:14 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_eat(t_philo *philo, t_data *data)
{
	grab_forks(philo, data);
	update_state(philo, IS_EATING, MSG_EAT, data);
	philo->last_meal_time_ms = get_timestamp_ms(data->start_time_ms);
	philo->meals_eaten++;
	if (data->meal_count != INFINITE && philo->meals_eaten >= data->meal_count)
	{
		philo->is_full = TRUE;
		sem_post(data->full_philos);
	}
	ft_sleep(data->time_to_eat, data);
	put_down_forks(data);
	return (SUCCESS);
}

static int	ph_sleep(t_philo *philo, t_data *data)
{
	update_state(philo, IS_SLEEPING, MSG_SLEEP, data);
	ft_sleep(data->time_to_sleep, data);
	return (SUCCESS);
}

int	ph_think(t_philo *philo, t_data *data)
{
	long	time;

	update_state(philo, IS_THINKING, MSG_THINK, data);
	time = get_time_left(philo, data);
	if (time)
		ft_sleep(time, data);
	else
		usleep(500);
	return (SUCCESS);
}

void	routine(t_philo *philo, t_data *data)
{
	sem_wait(data->dead_philos);
	if (data->meal_count != INFINITE)
		sem_wait(data->full_philos);
	if (data->number_of_philos == 1)
		usleep((data->time_to_die + 10) * 1000);
	if (philo->number % 2 == 0)
		ft_sleep(data->time_to_eat - 1, data);
	while (1)
	{
		ph_eat(philo, data);
		ph_sleep(philo, data);
		ph_think(philo, data);
	}
}
