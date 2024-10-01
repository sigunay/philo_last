/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:56:08 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/21 13:56:08 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

void	error_handle(int code, char **av, int flag)
{
	int	i;

	if (av && flag)
	{
		i = -1;
		while (av && av[++i])
			free(av[i]);
		free(av);
		if (code == MALLOCERR)
			write(1, "Malloc error!\n", 14);
	}
	if (code == ARGERR)
		write(1, "Arguments error!\n", 17);
}

void	ft_free(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philos;
	i = -1;
	if (philo)
		free(philo);
	if (data)
	{
		if (data->forks)
			while (++i < data->nbr_philo)
				pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->is_init_dc_mutex)
		pthread_mutex_destroy(&data->death_check);
	if (data->is_init_p_mutex)
		pthread_mutex_destroy(&data->print);
	i = 0;
}
