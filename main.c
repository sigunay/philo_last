/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:19 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/20 15:31:19 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	check_args(int ac, char **av)
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
	while (++i < data->nbr_of_philos)
	{
		if (pthread_create(&p[i].thread, NULL, &routines, &p[i]))
			return (1);
		p[i].last_meal_time = current_time();
	}
	check_death(data, p);
	ft_free(data);
	return (0);
}

static int	init_philo(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nbr_of_philos;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meal_count = 0;
		data->philos[i].data = data;
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	}
	return (0);
}

static int	init_data(t_data *data, int ac, char **av)
{
	data->nbr_of_philos = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->must_eat_count = ft_atoi(av[4]);
	else
		data->must_eat_count = -1;
	data->all_fed = 0;
	data->is_dead = 0;
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
	if (init_philo(data))
		return (1);
	return (0);
}
int	main(int argc, char **argv)
{
	t_data	data;
	int		flag;

	flag = 0;
	if ((argc != 5 && argc != 6 && argc != 2))
			return (simple_exit(ARGERR, NULL, flag), 1);
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		flag = 1;
		if (!argv || !*argv)
			return (simple_exit(MALLOCERR, argv, flag), 1);
	}
	else
		argv++;
	argc = find_len(argv);
	if (check_args(argc, argv))
		return (simple_exit(ARGERR, argv, flag), 1);
	if (init_data(&data, argc, argv))
		return (ft_free(&data), 1);
	if (create_threads(data.philos))
		return (ft_free(&data), write(1, "Create thread error!\n", 21), 1);
	return (0);
}
