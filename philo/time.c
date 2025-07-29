/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:26:55 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 18:58:48 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timeval_to_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	gettimeofday_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (timeval_to_ms(time));
}

long	get_timestamp_ms(long t0_ms)
{
	return (gettimeofday_ms() - t0_ms);
}

void	print_timestamp_ms(t_data *data, int num, char *msg)
{
	long	timestamp;

	timestamp = get_timestamp_ms(data->start_time_ms);
	pthread_mutex_lock(&data->print_lock);
	if (should_stop(FALSE, data))
	{
		pthread_mutex_unlock(&data->print_lock);
		return ;
	}
	printf("%ld %d %s", timestamp, num, msg);
	pthread_mutex_unlock(&data->print_lock);
}

long	get_time_left(t_philo *philo, t_data *data)
{
	long	time_left;
	long	time_passed;

	time_passed = get_timestamp_ms(data->start_time_ms)
		- philo->last_meal_time_ms;
	time_left = data->time_to_die - time_passed;
	if (time_left > 0)
		return (time_left);
	return (0);
}
