/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:08:06 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/22 19:08:06 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pick_up_forks(philo);
	print_status(philo, "is eating");
	philo->last_meal_time = current_time();
	usleep(data->time_to_eat * 1000);	// precise_sleep() hassas uyutma
	philo->meal_count++;
	put_down_forks(philo);
}
void	sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	print_status(philo, "is thinking");
}
int	check_death(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->death_check));
	if (current_time() - philo->last_meal_time > data->time_to_die)
	{
		print_status(philo, "died");
		data->is_dead = 1;
		pthread_mutex_unlock(&(data->death_check));
		return (1);
	}
	return (0);
}
