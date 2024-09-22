/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:42:40 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/20 15:55:36 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*new_arr;
	size_t	arr_len;
	size_t	i;

	arr_len = ft_strlen(s1);
	new_arr = (char *) malloc((arr_len + 1) * sizeof(char));
	if (new_arr == 0)
		return (0);
	i = 0;
	while (i < arr_len)
	{
		new_arr[i] = s1[i];
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}

static size_t	ft_min(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n2);
	return (n1);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	nstr_len;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	nstr_len = ft_strlen(s) - start;
	sub_str = malloc((ft_min(nstr_len, len) + 1) * sizeof(char));
	if (!sub_str)
		return (0);
	i = 0;
	while (i < len && s[i + start])
	{
		sub_str[i] = s[i + start];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
