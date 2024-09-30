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
#include <stdlib.h>

void	precise_sleep(t_data *data, long time)
{
	long long	start_time;

	start_time = current_time();
	while (!data->is_dead)
	{
		if (current_time() - start_time >= time)
			break;
		usleep(50);
	}
}

int	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pick_up_forks(philo))
		return (1);
	print_status(philo, "\033[31mis eating\033[0m");
	precise_sleep(data, data->time_to_eat);
	philo->last_meal_time = current_time();
	philo->meal_count++;
	put_down_forks(philo);
	return (0);
}
void	sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is sleeping");
	precise_sleep(data, data->time_to_sleep);
	print_status(philo, "is thinking");
}
void	check_death(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->all_fed)
	{
		i = -1;
		while (++i < data->nbr_of_philos && !data->is_dead)
		{
			pthread_mutex_lock(&data->death_check);
			if (current_time() - philo[i].last_meal_time > data->time_to_die)
			{
				print_status(philo, "died");
				data->is_dead = 1;
			}
			pthread_mutex_unlock(&data->death_check);
			usleep(100);
		}
		if (data->is_dead)
			break;
		i = 0;
		while (data->must_eat_count != -1 && i < data->nbr_of_philos && philo[i].meal_count >= data->must_eat_count)
			i++;
		if (i == data->nbr_of_philos)
			data->all_fed = 1;
	}
}
