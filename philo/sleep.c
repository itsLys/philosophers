/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:55:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 11:55:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleep_in_chuncks(long time, t_data *data)
{
	long	start;

	start = get_timestamp_ms(data->start_time_ms);
	while (get_timestamp_ms(data->start_time_ms) - start < time)
	{
		if (should_stop(FALSE, data))
			break;
		usleep(100);
	}
}

void	ft_sleep(long time, t_data *data)
{
	long	start;

	if (time == 0)
		return ;
	start = get_timestamp_ms(data->start_time_ms);
	ft_sleep_in_chuncks(time, data);
	while (should_stop(FALSE, data) == FALSE && get_timestamp_ms(data->start_time_ms) - start < time)
		;
}
