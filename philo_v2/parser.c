/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:37:19 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/27 20:30:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_num(char *str)
{
	int	n;

	n = 0;
	if (*str == '\0')
		return (ERROR);
	while (*str && *str >= '0' && *str <= '9')
		n = (*(str++) - '0') + n * 10;
	if (*str)
		return (ERROR);
	return (n);
}

int parse_args(int ac, char **av, t_data *data)
{
	data->number_of_philos = parse_num(av[1]);
	data->time_to_die = parse_num(av[2]);
	data->time_to_eat = parse_num(av[3]);
	data->time_to_sleep = parse_num(av[4]);
	if (ac >= 5)
	{
		data->meal_count = parse_num(av[5]);
		if (data->meal_count == ERROR)
			return (printf(MSG_USAGE), ERROR);
	}
	else
		data->meal_count = -1;
	if (data->number_of_philos == ERROR
			|| data->time_to_die == ERROR
			|| data->time_to_eat == ERROR
			|| data->time_to_sleep == ERROR)
		return (printf(MSG_USAGE), ERROR);
	else
		return (EXIT_SUCCESS);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (parse_args(ac, av, data) == ERROR)
		return ERROR;
	data->start_time_ms = gettimeofday_ms();
	data->should_stop = FALSE;
	if (pthread_mutex_init(&data->state_guard, NULL)
			|| pthread_mutex_init(&data->output_guard, NULL))
		return ERROR;
	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	t_data	*data;
	int		created;

	if (argc != 5 && argc != 6)
		return (printf(MSG_USAGE), EXIT_FAILURE);
	data = ft_malloc(sizeof(t_data));
	if (data == NULL)
		return EXIT_FAILURE;
	if (init_data(argc, argv, data) == ERROR)
		return (printf(MSG_USAGE), free(data), EXIT_FAILURE);
	created = init_philosophers(data);
	if (created < data->number_of_philos)
		return (free_resources(created, data), EXIT_FAILURE);
	// monitor
	return EXIT_SUCCESS;
}
