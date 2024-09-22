/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:32:56 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/20 15:32:56 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_num(char c)
{
	if (c < '0' || c > '9')
		return (1);
	return (0);
}

static int	is_white_space(char x)
{
	if (x == 32 || x == 9 || x == 10 || x == 11 || x == 12 || x == 13)
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}
