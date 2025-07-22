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


/* full: full philosopher: number of philosophers that have eaten enough */

int check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (is_starving(data->philosophers + i, data))
		{
			update_state(data->philosophers + i, IS_DEAD, MSG_DIED, data);
			should_stop(TRUE, data);
			return FAILURE;
		}
		i++;
	}
	return SUCCESS;
}

int	is_full(t_philo *philo, t_data *data)
{
	int	is_full;

	pthread_mutex_lock(&data->state_lock);
	is_full = philo->is_full;
	pthread_mutex_unlock(&data->state_lock);
	return is_full;
}

int check_full(t_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (i < data->number_of_philos)
	{
		if (is_full(data->philosophers + i, data))
			n++;
		i++;
	}
	if (n == data->number_of_philos)
	{
		should_stop(TRUE, data);
		return FAILURE;
	}
	return  SUCCESS;
}

void monitor(t_data *data)
{
	usleep(500);
	while (1)
	{
		if (check_death(data))
			return ;
		if (data->meal_count > -1 && check_full(data))
			return ;
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
