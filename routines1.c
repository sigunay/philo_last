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
#include <stdio.h>

void	precise_sleep(t_data *data, long time)
{
	long long	start_time;

	start_time = current_time();
	while (!data->is_dead)
	{
		if (current_time() - start_time >= time)
			break ;
		usleep(50);
	}
}

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
		pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	check_death(t_data *data, t_philo *p)
{
	int	i;

	while (!data->all_fed)
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->death_check);
			if (current_time() - p[i].last_meal_time > data->time_to_die)
			{
				print_status(p, "died");
				data->is_dead = 1;
			}
			pthread_mutex_unlock(&data->death_check);
			usleep(100);
		}
		if (data->is_dead)
			break ;
		i = -1;
		while (data->must_ec != -1 && ++i < data->nbr_philo
			&& p[i].meal_count + 1 >= data->must_ec)
			;
		if (i == data->nbr_philo)
			data->all_fed = 1;
	}
}
