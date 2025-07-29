/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:52:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/27 16:05:56 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void clear_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_close(data->dead_philos);
	sem_close(data->full_philos);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD_PHILOS);
	sem_unlink(SEM_FULL_PHILOS);
}

void clean_exit(int status, t_data *data)
{
	clear_semaphores(data);
	free(data->philosophers);
	exit(status);
}

void	kill_children(int created, t_data *data)
{
	int i;

	i = 0;
	while (i < created)
		kill(data->philosophers[i++].pid, SIGKILL);
	i = 0;
	while (i < created)
		waitpid(data->philosophers[i++].pid, NULL, 0);
}
