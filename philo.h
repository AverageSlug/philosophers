/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:11 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:09:18 by nlaurids         ###   ########.fr       */
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
	int	left;
	int	right;
	int	status;
	int	time;
	int	time_last_eat;
}	t_threads;

typedef struct s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				wincon;
	int				index;
	pthread_t		*pthread;
	pthread_mutex_t	*mutex;
}	t_philo;

void	*ft_philoop(void *args);
int		ft_parse(int n, char **args, t_philo *philo);
int		ft_atoi(char *str);
int		ft_is_num(char *str);
int		ft_clearall(int ret, t_philo *philo);

#endif
