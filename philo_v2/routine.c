/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:39:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 17:02:44 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// t_state read_state(t_philo *philosopher, t_data *data)
// {
// 	t_state	state;
//
// 	pthread_mutex_lock(&data->state_guard);
// 	state = philosopher->state;
// 	pthread_mutex_unlock(&data->state_guard);
// 	return  state;
// }

void ph_eat(t_philo *philosopher, t_data *data)
{
	if (read_state(philosopher, data) == IS_DEAD)
		return ;
	grab_forks(philosopher, data);
	update_state(philosopher, IS_EATING, MSG_EAT, data);
	update_last_meal(philosopher, data);
	update_meal_count(philosopher, data);
	ft_sleep(data->time_to_eat, data);
	put_down_forks(philosopher, data);
}

void ph_sleep(t_philo *philosopher, t_data *data)
{
	if (read_state(philosopher, data) == IS_DEAD)
		return ;
	update_state(philosopher, IS_SLEEPING, MSG_SLEEP, data);
	ft_sleep(data->time_to_sleep, data);
}

void ph_think(t_philo *philosopher, t_data *data)
{
	if (read_state(philosopher, data) == IS_DEAD)
		return ;
	update_state(philosopher, IS_THINKING, MSG_THINK, data);
}

int should_stop(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (read_state(data->philosophers + i, data) == IS_DEAD && printf("%d dieeeeeed\n", i))
			return TRUE;
		i++;
	}
	return FALSE;
}

void *routine(void *arg)
{
	t_data	*data;
	t_philo	*philosopher;
	(void) data;
	data = ((t_args *) arg)->data;
	philosopher = ((t_args *) arg)->philosopher;
	while (1)
	{
		
		if (should_stop(data) && printf("should stop true\n"))
			return NULL ;
		ph_eat(philosopher, data);
		ph_sleep(philosopher, data);
		ph_think(philosopher, data);
	}
	return NULL;
}
