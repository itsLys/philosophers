/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:29:55 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/26 10:53:58 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void clear_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
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
		kill(data->philosophers[i].pid, SIGTERM);
	i = 0;
	while (i < created)
		waitpid(data->philosophers[i].pid, NULL, 0);
}
