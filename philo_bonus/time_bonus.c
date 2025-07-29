/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:26:55 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 15:49:13 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_timestamp_ms(t_data *data, t_philo *philo, char *msg)
{
	long	timestamp;

	timestamp = get_timestamp_ms(data->start_time_ms);
	sem_wait(data->print_lock);
	printf("%ld %d %s", timestamp, philo->number, msg);
	if (philo->state != IS_DEAD)
		sem_post(data->print_lock);
}
