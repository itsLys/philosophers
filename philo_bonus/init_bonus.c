/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/18 19:02:29 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void free_resources(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	free(data->philosophers);
}

int	init_semaphores(t_data *data)
{
	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
					0644, data->number_of_philos);
	data->print_lock = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
					0644, data->number_of_philos);
	if (data->forks == SEM_FAILED || data->print_lock == SEM_FAILED)
		return ERROR;
	return SUCCESS;
}

int init_philosophers(t_data *data)
{
	int		i;

	while (i < data->number_of_philos)
	{
		data->philosophers[i].number = i + 1;
		data->philosophers[i].state = -1;
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid == 0)
		{
			routine(data->philosophers + i, data);
			return (free_resources(data), exit(0), SUCCESS);
		}
		else if (data->philosophers[i].pid == ERROR)
			return (free_resources(data), exit(1), FAILURE);
		i++;
	}
}

int	init_data(int ac, char **av, t_data *data)
{
	if (parse_args(ac, av, data) == ERROR)
		return (printf(MSG_USAGE), ERROR);
	if (init_semaphores(data) == ERROR)
		return (free_resources(data), ERROR);
	data->start_time_ms = gettimeofday_ms();
	data->should_stop = FALSE;
	data->philosophers = ft_malloc(data->number_of_philos);
	if (data->philosophers == NULL)
		return (free_resources(data), ERROR);
	return (EXIT_SUCCESS);
}

