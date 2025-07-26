/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:42:07 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/26 10:42:15 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	update_state(t_philo *philosopher, t_state state, char *msg, t_data *data)
{
	philosopher->state = state;
	print_timestamp_ms(data, philosopher->number, msg);
}
