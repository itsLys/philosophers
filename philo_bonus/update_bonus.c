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
	print_timestamp_ms(data, philosopher, msg);
}
