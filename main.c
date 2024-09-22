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

static int	find_len(char **arr)
{
	int				i;
	unsigned int	len;

	len = 0;
	i = -1;
	while (arr[++i])
		len++;
	return (len);
}

static int	check_args(int ac, char **av)
{
	int		i;
	int		j;

	if (ac != 4 && ac != 5)
		return (1);
	i = 0;
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

static void create_threads(t_philo *p)
{
	t_data	*data;
	int		i;

	data = p->data;
	i = -1;
	data->start_time = current_time();
	while (++i < data->nbr_of_philos)	//create threads
		{
			data->philos[i].last_meal_time = data->start_time;
			pthread_create(&p[i].thread, 0, &routines,&p[i]);
		}
	i = -1;
	while (++i < data->nbr_of_philos)	// wait threads
		pthread_join(p[i].thread, NULL);
	i = -1;
	while (++i < data->nbr_of_philos)	// clean mutex
		pthread_mutex_destroy(&data->forks[i]);
	ft_free(data);	// free data.philos and data.forks
}

static void	init_data(t_data *data, int ac, char **av)
{
	int	i;

	data->nbr_of_philos = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[4]);
	else
		data->must_eat_count = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos); //çatalları oluştur /free malloc kontrolleri eklensin
	i = -1;
	while (++i < data->nbr_of_philos)
		pthread_mutex_init(&data->forks[i], NULL); // mutex init
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos); //filozof dizisi oluşturuldu /free
	i = -1;
	while (++i < data->nbr_of_philos)	// filozofların bilgileri girildi.
	{
		data->philos[i].id = i;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meal_count = 0;
		data->philos[i].data = data;
	}
	data->is_dead = 0;
	create_threads(data->philos);
}
// data detaylı init edildi artık rutinler yazılmalı 21.09.2024 23:09 iyi çalıştın. ertesi gün bu iş sende
int	main(int argc, char **argv)
{
	t_data	data;
	//int		i;

	if ((argc != 5 && argc != 6 && argc != 2))
			simple_exit(ARGERR, NULL);
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');	// freelenmeli
		if (!argv || !*argv)
			simple_exit(MALLOCERR, argv);
	}
	else
		argv++;
	argc = find_len(argv);
	if (check_args(argc, argv))
		simple_exit(ARGERR, argv);
	init_data(&data, argc, argv);

	/*	TEST
	i = -1;
	while (++i < data.nbr_of_philos)
	{
		printf("data[%d] nbr_of_philo: %d\n", i, data.philos->data->nbr_of_philos);
		printf("data[%d] time_to_eat: %d\n", i, data.philos->data->time_to_eat);
		printf("data[%d] time_to_sleep: %d\n", i, data.philos->data->time_to_sleep);
		printf("data[%d] time_to_di: %d\n", i, data.philos->data->time_to_die);
		printf("data[%d] must_eat_count: %d\n", i, data.philos->data->must_eat_count);
		printf("data[%d] forks: %p\n", i, &data.philos->data->forks[i]);
	}

	i = -1;
	while (++i < data.nbr_of_philos)
	{
		printf("philos[%d] id : %d\n", i, data.philos[i].id);
		printf("philos[%d] last_meal_time : %d\n", i, data.philos[i].last_meal_time);
		printf("philos[%d] meal_count : %d\n", i, data.philos[i].meal_count);
		printf("philos[%d] thread : %ld\n", i, data.philos[i].thread);
	}*/

	// argv freeleme fonksiyonu yaz
}
