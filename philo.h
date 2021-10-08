/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:11 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/08 14:29:15 by nlaurids         ###   ########.fr       */
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

typedef struct s_threads
{
	int	initial_time;
	int	left;
	int	status;
	int	time;
	int	last_eat;
	int	win;
	int	done;
}	t_threads;

typedef struct s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				wincon;
	int				index;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	dead;
	t_threads		*threads;
}	t_philo;

unsigned long	ft_set_time(void);
void			*ft_checkloop(void *args);
void			*ft_philoop(void *args);
int				ft_parse(int n, char **args, t_philo *philo);
int				ft_atoi(char *str);
int				ft_is_num(char *str);
int				ft_clearall(t_philo *philo);

#endif
