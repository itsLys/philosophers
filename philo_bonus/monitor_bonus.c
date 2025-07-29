/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:46:03 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/29 16:47:14 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_starving(t_philo *philo, t_data *data)
{
	if (get_timestamp_ms(data->start_time_ms)
		- philo->last_meal_time_ms
		> data->time_to_die)
		return (TRUE);
	return (FALSE);
}

/* if someone died, he posts the needed number of full phislosphers
 * 	which will triger the loop to end, and thus going to the next instruction*/
void	track_meal_count(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		sem_wait(data->full_philos);
		i++;
	}
	sem_post(data->dead_philos);
}

void	monitor(t_data *data)
{
	usleep(1000);
	if (data->meal_count != INFINITE)
		track_meal_count(data);
	sem_wait(data->dead_philos);
	kill_children(data->number_of_philos, data);
	clean_exit(SUCCESS, data);
}
