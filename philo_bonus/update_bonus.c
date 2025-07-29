/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:47:42 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 15:47:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unblock_monitor(t_data *data)
{
	int	i;

	if (data->meal_count != INFINITE)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			sem_post(data->full_philos);
			i++;
		}
	}
}

void	update_state(t_philo *philo, t_state state, char *msg, t_data *data)
{
	philo->state = state;
	if (is_starving(philo, data))
	{
		print_timestamp_ms(data, philo, MSG_DIED);
		philo->state = IS_DEAD;
		unblock_monitor(data);
		sem_post(data->dead_philos);
		return ;
	}
	print_timestamp_ms(data, philo, msg);
}
