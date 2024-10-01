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
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_data	data;
	int		flag;

	flag = 0;
	if ((argc != 5 && argc != 6 && argc != 2))
		return (error_handle(ARGERR, NULL, flag), 1);
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		flag = 1;
		if (!argv || !*argv)
			return (error_handle(MALLOCERR, argv, flag), 1);
	}
	else
		argv++;
	argc = find_len(argv);
	if (check_args(argc, argv))
		return (error_handle(ARGERR, argv, flag), 1);
	if (init_data(&data, argc, argv))
		return (error_handle(0, argv, flag), 1);
	if (create_threads(data.philos))
		return (ft_free(&data), write(1, "Create thread error!\n", 21), 1);
	error_handle(0, argv, flag);
	return (0);
}
