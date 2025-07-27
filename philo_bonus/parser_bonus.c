/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:37:19 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 15:59:44 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (ac >= 6)
	{
		data->meal_count = parse_num(av[5]);
		if (data->meal_count == ERROR)
			return (ERROR);
	}
	else
		data->meal_count = -1;
	if (data->number_of_philos == ERROR
			|| data->time_to_die == ERROR
			|| data->time_to_eat == ERROR
			|| data->time_to_sleep == ERROR)
		return (ERROR);
	else
		return (EXIT_SUCCESS);
}
