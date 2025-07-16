/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:26:55 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 12:51:59 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timeval_to_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	gettimeofday_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (timeval_to_ms(time));
}

long	get_timestamp_ms(long t0_ms)
{
	return (gettimeofday_ms() - t0_ms);
}

void print_timestamp_ms(t_data *data, int num, char *msg)
{
	long	timestamp;

	timestamp = get_timestamp_ms(data->start_time_ms);
	pthread_mutex_lock(&data->print_guard);
	printf("%ld %d %s", timestamp, num, msg);
	pthread_mutex_unlock(&data->print_guard);
}
