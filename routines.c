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
#include <unistd.h>

void	sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->is_dead == 1)
		return ;
	print_status(philo, "is sleeping");
	precise_sleep(data, data->time_to_sleep);
	print_status(philo, "is thinking");
}

int	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pick_up_forks(philo))
		return (1);
	print_status(philo, "is eating");
	precise_sleep(data, data->time_to_eat);
	philo->last_meal_time = current_time();
	philo->meal_count++;
	put_down_forks(philo);
	return (0);
}

void	*routines(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!data->is_dead)
	{
		if (eat(philo))
			return (NULL);
		if (data->all_fed)
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
