/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:29:28 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 09:45:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return NULL;
	memset(ptr, 0, size);
	return ptr;
}

int		is_even(int n)
{
	return (n % 2 == 0);
}

void	ft_sleep(long time, t_data *data)
{
	long start = get_timestamp_ms(data->start_time_ms);
	while (get_timestamp_ms(data->start_time_ms) - start < time)
	{
		if (should_stop(FALSE, data))
			break;
		usleep(10);
	}
}
