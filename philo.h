/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sigunay <sigunay@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:57 by sigunay           #+#    #+#             */
/*   Updated: 2024/09/20 15:31:57 by sigunay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

// HATA KODLARINI DOĞRU YAZDIRMAK İÇİN EXİT FONKSİYONU DEFİNELARI
//#define USAGERR = 1 muhtemelen gereksiz
# define ARGERR 2
# define MALLOCERR 3


//structs
typedef struct s_philo t_philo;
typedef struct s_data
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;		// çatallar mutex olarak tutulacak
	t_philo			*philos;	// filozoflar dizisi
} t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			last_meal_time;
	int			meal_count;
	t_data		*data;		// filozofun genel verilere erişimi için
} t_philo;

//funcs		NORM KONTROLLERİNİ UNUTMA (KÜTÜPHANE STATİC VS.)
void	ft_free(t_data *data);
void	*routines(void *arg);
void	simple_exit(int code, char **av);
int		ft_is_num(char c);
int		ft_atoi(const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);

# endif