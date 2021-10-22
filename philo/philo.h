/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:11 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/22 14:09:50 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_philo;

typedef struct s_threads
{
	int				index;
	int				left;
	int				status;
	int				time;
	int				done;
	struct s_philo	*philo;
}	t_threads;

typedef struct s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				init;
	int				wincon;
	int				win;
	int				*last;
	int				*limit;
	int				end;
	pthread_t		*pthread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	write;
	pthread_mutex_t	protect;
	pthread_mutex_t	exit;
	t_threads		*threads;
}	t_philo;

unsigned long	ft_set_time(void);
void			ft_usleep(unsigned long sleep_time, t_threads *threads);
int				ft_print(int j, t_threads *threads);
void			*ft_checkloop(void *args);
void			*ft_philoop(void *args);
int				ft_parse(int n, char **args, t_philo *philo);
int				ft_atoi(const char *str);
int				ft_is_num(char *str);
int				ft_clearall(t_philo *philo);

#endif
