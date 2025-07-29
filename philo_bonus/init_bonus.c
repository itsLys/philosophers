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
	// refactor -1 to INFINIT
	if ( data->meal_count != INFINITE )
		data->full_philos = sem_open(SEM_FULL_PHILOS, O_CREAT | O_EXCL,
					0644, data->number_of_philos);
	if (data->dead_philos == SEM_FAILED
			|| data->forks == SEM_FAILED
			|| data->print_lock == SEM_FAILED
			|| (data->meal_count != INFINITE && data->full_philos == SEM_FAILED))
		return ERROR;
	return SUCCESS;
}

int init_philosophers(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philosophers[i].number = i + 1;
		data->philosophers[i].state = -1;
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid == 0)
		{
			routine(data->philosophers + i, data);
			clean_exit(SUCCESS, data);
		}
		else if (data->philosophers[i].pid == ERROR)
			return (i);
		i++;
	}
	return i;
}

int	init_data(int ac, char **av, t_data *data)
{
	if (parse_args(ac, av, data) == ERROR)
		return (printf(MSG_USAGE), ERROR);
	if (init_semaphores(data) == ERROR)
		return (clear_semaphores(data), ERROR);
	data->start_time_ms = gettimeofday_ms();
	data->should_stop = FALSE;
	data->philosophers = ft_malloc(data->number_of_philos * sizeof(t_philo));
	if (data->philosophers == NULL)
		return (clear_semaphores(data), ERROR);
	return (EXIT_SUCCESS);
}
