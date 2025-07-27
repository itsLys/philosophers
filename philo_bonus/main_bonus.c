/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:23:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/23 10:47:33 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char **argv)
{
	t_data	data;
	int		created;

	if (argc != 5 && argc != 6)
		return (printf(MSG_USAGE), EXIT_FAILURE);
	if (init_data(argc, argv, &data) == ERROR)
		return (EXIT_FAILURE);
	// created = init_forks(&data);
	// if (created < data.number_of_philos)
	// 	return (destroy_forks(created, &data), EXIT_FAILURE);
	created = init_philosophers(&data);
	if (created < data.number_of_philos)
		return (destroy_forks(created, &data),
				detach_threads(created, &data),
				EXIT_FAILURE);
	monitor(&data);
	free_resources(&data);
	return EXIT_SUCCESS;
}
