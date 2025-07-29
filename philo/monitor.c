/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:46:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 12:04:01 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(int set, t_data *data)
{
	int	should_stop;

	pthread_mutex_lock(&data->simulation);
	if (set)
		data->should_stop = TRUE;
	should_stop = data->should_stop;
	pthread_mutex_unlock(&data->simulation);
	return (should_stop);
}

static int	check_full(t_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (i < data->number_of_philos)
	{
		if (is_full(data->philos + i, data))
			n++;
		i++;
	}
	if (n == data->number_of_philos)
	{
		should_stop(TRUE, data);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (is_starving(data->philos + i, data))
		{
			update_state(data->philos + i, IS_DEAD, MSG_DIED, data);
			should_stop(TRUE, data);
			return (FAILURE);
		}
		i++;
		usleep(500);
	}
	return (SUCCESS);
}

void	monitor(t_data *data)
{
	usleep(500);
	while (1)
	{
		if (check_death(data))
			return ;
		if (data->meal_count > -1 && check_full(data))
			return ;
	}
}
