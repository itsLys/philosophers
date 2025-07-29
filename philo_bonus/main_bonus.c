/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:23:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 16:06:10 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void monitor(t_data *data)
{
	int i;

	i = 0;
	while (i < data->meal_count)
	{
		sem_wait(data->full_philos);
		i++;
		if (i == data->meal_count)
			sem_post(data->dead_philos);
	}
	sem_wait(data->dead_philos);
	usleep((data->time_to_die * 1000));
	kill_children(data->number_of_philos, data);
	clean_exit(SUCCESS, data);
}

int main(int argc, char **argv)
{
	t_data	data;
	int		created;

	if (argc != 5 && argc != 6)
		return (printf(MSG_USAGE), EXIT_FAILURE);
	if (init_data(argc, argv, &data) == ERROR)
		return (EXIT_FAILURE);
	created = init_philosophers(&data);
	if (created < data.number_of_philos)
	{
		// ;
		kill_children(created, &data);
		clean_exit(FAILURE, &data);
	}
	monitor(&data);
	// kill_children(created, &data);
	// clean_exit(FAILURE, &data);

}
