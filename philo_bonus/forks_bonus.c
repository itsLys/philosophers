/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:41:03 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/26 10:47:21 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void grab_forks(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
}

void put_down_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}
