/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:23:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 10:07:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				should_stop(TRUE, data);
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
		return (destroy_forks(created, &data), EXIT_FAILURE);
	created = init_philosophers(&data);
	if (created < data.number_of_philos)
		return (destroy_forks(created, &data),
				detach_threads(created, &data),
				EXIT_FAILURE);
	monitor(&data);
	free_resources(&data);
	return EXIT_SUCCESS;
}
