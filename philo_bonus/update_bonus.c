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

void	update_state(t_philo *philosopher, t_state state, char *msg, t_data *data)
{
	philosopher->state = state;
	if (is_starving(philosopher, data))
	{
		print_timestamp_ms(data, philosopher, MSG_DIED);
		philosopher->state = IS_DEAD;
		sem_post(data->dead_philos);
		return ;
	}
	if (philosopher->is_full)
		sem_post(data->full_philos);
	print_timestamp_ms(data, philosopher, msg);
}
