/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:27:42 by sigunay           #+#    #+#             */
/*   Updated: 2024/10/01 16:42:52 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	check_args(int ac, char **av)
{
	int		i;
	int		j;

	if (ac != 4 && ac != 5)
		return (1);
	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (ft_is_num(av[i][j]) && av[i][j] != '+')
				return (1);
		}
	}
	return (0);
}

int	create_threads(t_philo *p)
{
	t_data	*data;
	int		i;

	data = p->data;
	i = -1;
	data->start_time = current_time();
	while (++i < data->nbr_philo)
	{
		if (pthread_create(&p[i].thread, NULL, &routines, &p[i]))
			return (1);
		p[i].last_meal_time = current_time();
	}
	check_death(data, p);
	i = -1;
	while (++i < data->nbr_philo && p[i].thread)
		pthread_join(p[i].thread, NULL);
	ft_free(data);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&data->death_check, 0))
	{
		data->is_init_dc_mutex = 0;
		return (1);
	}
	data->is_init_dc_mutex = 1;
	if (pthread_mutex_init(&data->print, 0))
	{
		data->is_init_p_mutex = 0;
		return (1);
	}
	data->is_init_p_mutex = 1;
	return (0);
}

int	init_philo(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nbr_philo;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meal_count = 0;
		data->philos[i].data = data;
	}
	if (init_mutexes(data))
		return (1);
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nbr_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->must_ec = ft_atoi(av[4]);
	else
		data->must_ec = -1;
	if (data->must_ec == 0)
		return (1);
	data->all_fed = 0;
	data->is_dead = 0;
	if (init_philo(data))
		return (1);
	return (0);
}
