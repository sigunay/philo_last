/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_routines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:15:42 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/22 16:15:42 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	print_status(t_philo *philo, const char *status)
{
	long	timestamp;

	timestamp = current_time();
	printf("%ld %d %s\n", timestamp, philo->id, status);
}

void	pick_up_forks(t_philo *philo)
{
	t_data	*data;
	
	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->id]));
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&(data->forks[(philo->id + 1) % data->nbr_of_philos]));
	print_status(philo, "has taken a fork");
}

void	put_down_forks(t_philo *philo) 
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&(data->forks[philo->id]));
	pthread_mutex_unlock(&(data->forks[(philo->id + 1) % data->nbr_of_philos]));
}

void	*routines(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo*)arg;
	data = philo->data;

	if (philo->id % 2)	// geciktirici!
		usleep(15000);
	while (!data->is_dead)
	{
		if (check_death(philo))
			break;
		eat(philo);
		if (check_death(philo))
			break;
		sleep_and_think(philo);
	}
	return (NULL);
}
