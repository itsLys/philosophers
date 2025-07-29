/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 15:59:44 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD_PHILOS);
	sem_unlink(SEM_FULL_PHILOS);
	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
			0644, data->number_of_philos);
	data->print_lock = sem_open(SEM_PRINT, O_CREAT | O_EXCL,
			0644, 1);
	data->dead_philos = sem_open(SEM_DEAD_PHILOS, O_CREAT | O_EXCL,
			0644, data->number_of_philos);
	if (data->meal_count != INFINITE)
		data->full_philos = sem_open(SEM_FULL_PHILOS, O_CREAT | O_EXCL,
				0644, data->number_of_philos);
	if (data->dead_philos == SEM_FAILED
		|| data->forks == SEM_FAILED
		|| data->print_lock == SEM_FAILED
		|| (data->meal_count != INFINITE && data->full_philos == SEM_FAILED))
		return (ERROR);
	return (SUCCESS);
}

int	init_philos(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].number = i + 1;
		data->philos[i].state = -1;
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			routine(data->philos + i, data);
			clean_exit(SUCCESS, data);
		}
		else if (data->philos[i].pid == ERROR)
			return (i);
		i++;
	}
	return (i);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (parse_args(ac, av, data) == ERROR)
		return (printf(MSG_USAGE), ERROR);
	if (init_semaphores(data) == ERROR)
		return (clear_semaphores(data), ERROR);
	data->start_time_ms = gettimeofday_ms();
	data->should_stop = FALSE;
	data->philos = ft_malloc(data->number_of_philos * sizeof(t_philo));
	if (data->philos == NULL)
		return (clear_semaphores(data), ERROR);
	return (EXIT_SUCCESS);
}
