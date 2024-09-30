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
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				all_fed;
	long long			start_time;
	int				is_dead;	// ölüm kontrolü
	pthread_mutex_t	death_check;	//ölüm kontrol mutexi
	int				is_init_dc_mutex;
	pthread_mutex_t	print;
	int				is_init_p_mutex;
} t_data;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	pthread_t	thread;
	long long		last_meal_time;
	int			meal_count;
	t_data		*data;
} t_philo;

//funcs		NORM KONTROLLERİNİ UNUTMA (KÜTÜPHANE STATİC VS.)
void		ft_free(t_data *data);
int			find_len(char **arr);
void		check_death(t_data *data, t_philo *philo);
void		sleep_and_think(t_philo *philo);
int			eat(t_philo *philo);
void		print_status(t_philo *philo, const char *status);
void		put_down_forks(t_philo *philo);
int			pick_up_forks(t_philo *philo);
long long	current_time(void);
void		ft_free(t_data *data);
void		*routines(void *arg);
void		simple_exit(int code, char **av, int flag);
int			ft_is_num(char c);
int			ft_atoi(const char *str);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(const char *s, char c);

# endif