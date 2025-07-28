/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:00:54 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 16:13:29 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void grab_forks(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	print_timestamp_ms(data, philo, MSG_TAKE);
	sem_wait(data->forks);
	print_timestamp_ms(data, philo, MSG_TAKE);
}

void put_down_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}
