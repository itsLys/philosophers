/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:39:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 19:04:03 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philo *philosopher, t_data *data)
{
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
	update_state(philosopher, IS_THINKING, MSG_THINK, data);
	return  SUCCESS;
}

void *routine(void *arg)
{
	t_data	*data;
	t_philo	*philosopher;
	(void) data;
	data = ((t_args *) arg)->data;
	philosopher = ((t_args *) arg)->philosopher;
	while (should_stop(FALSE, data) == 0)
	{
		ph_eat(philosopher, data);
		ph_sleep(philosopher, data) ;
		ph_think(philosopher, data);
	}
	return NULL;
}
