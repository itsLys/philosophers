/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:39:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 12:10:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philo *philo, t_data *data)
{
	grab_forks(philo, data);
	update_state(philo, IS_EATING, MSG_EAT, data);
	update_last_meal(philo, data);
	update_meal_count(philo, data);
	ft_sleep(data->time_to_eat, data);
	put_down_forks(philo, data);
	return (SUCCESS);
}

int	ph_sleep(t_philo *philo, t_data *data)
{
	update_state(philo, IS_SLEEPING, MSG_SLEEP, data);
	ft_sleep(data->time_to_sleep, data);
	return (SUCCESS);
}

int	ph_think(t_philo *philo, t_data *data)
{
	long	time_left;

	time_left = get_time_left(philo, data);
	update_state(philo, IS_THINKING, MSG_THINK, data);
	if (time_left)
		ft_sleep(time_left, data);
	else
		usleep(600);
	return (SUCCESS);
}

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = ((t_args *) arg)->data;
	philo = ((t_args *) arg)->philo;
	if (data->number_of_philos == 1)
		usleep((data->time_to_die + 10) * 1000);
	while (should_stop(FALSE, data) == 0)
	{
		ph_eat(philo, data);
		ph_sleep(philo, data);
		ph_think(philo, data);
	}
	return (NULL);
}
