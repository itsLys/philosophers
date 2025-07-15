/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:23:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/15 17:10:37 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_starving(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->state_guard);
	if (get_timestamp_ms(data->start_time_ms)
			- philo->last_meal_time_ms
			>= data->time_to_die)
	{
		pthread_mutex_unlock(&data->state_guard);
		return TRUE;
	}
	pthread_mutex_unlock(&data->state_guard);
	return FALSE;
}

// now that you set the philo state to dead
// go on and make the philo not update its state if he is dead, and thnk of how to exit the program 
void monitor(t_data *data)
{
	int i;

	usleep(500);
	i = 0;
	while (1)
	{
		while (i < data->number_of_philos)
		{
			if (is_starving(data->philosophers + i, data))
			{
				update_state(data->philosophers + i, IS_DEAD, MSG_DIED, data);
				return;
			}
			i++;
		}
		i = 0;
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	int		created;

	if (argc != 5 && argc != 6)
		return (printf(MSG_USAGE), EXIT_FAILURE);
	if (init_data(argc, argv, &data) == ERROR)
		return (printf(MSG_USAGE), EXIT_FAILURE);
	created = init_forks(&data);
	if (created < data.number_of_philos)
		return (destroy_mutexes(created, &data), EXIT_FAILURE);
	created = init_philosophers(&data);
	if (created < data.number_of_philos)
		return (destroy_mutexes(created, &data),
				detach_threads(created, &data),
				EXIT_FAILURE);
	monitor(&data);
	free_resources(&data);
	return EXIT_SUCCESS;
}
