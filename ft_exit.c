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

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <stdio.h>

void	simple_exit(int code, char **av)
{
	int	i;

	i = -1;
	if (code == ARGERR)
	{
		while (av && av[++i])
			free(av[i]);
		free(av);
		write(1, "Arguments error!\n", 17);
		exit(ARGERR);
	}
	if (code == MALLOCERR)
	{
		while (av[++i])
			free(av[i]);
		free(av);
		write(1, "Malloc error!\n", 14);
		exit(MALLOCERR);
	}
}
void	ft_free(t_data *data)
{
	free(data->forks);
	free(data->philos);
}