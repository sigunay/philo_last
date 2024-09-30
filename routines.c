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
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print);
	if (!data->is_dead)
	{
		printf("%lld ", current_time() - data->start_time);
		printf("%d ", philo->id + 1);
		printf("%s\n", status);
	}
	pthread_mutex_unlock(&data->print);
}

int	pick_up_forks(t_philo *philo)
{
	t_data	*data;
	
	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	print_status(philo, "has taken a fork");
	if (philo->right_fork != philo->left_fork)
	{
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		print_status(philo, "has taken a fork");
		return (0);
	}
	return (1);
}

void	put_down_forks(t_philo *philo) 
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	if (philo->right_fork != philo->left_fork)
		pthread_mutex_unlock(&(data->forks[(philo->right_fork) % data->nbr_of_philos]));
}

void	*routines(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo*)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!data->is_dead)
	{
		if (eat(philo))
			return (NULL);
		if (data->all_fed)
			break;
		sleep_and_think(philo);
	}
	return (NULL);
}
