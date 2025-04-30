/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:20:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/04/17 16:39:54 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

# define ERROR -1
# define SUCCESS 0

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef struct s_philo
{
	pthread_t		philo;
	int				philo_num;
	t_state			state;
	int				fork;
	struct s_philo	*left_philo;
}	t_philo ;

typedef struct s_data
{
	t_philo	*philos;
	int		philos_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_count;
}		t_data ;

int	parse_num(char *str);
int	parse_args(int ac, char **av, t_data *data);
#endif // !PHILO_H
