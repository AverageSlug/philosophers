/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:17 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/08 14:52:18 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned long sleep_time)
{
	unsigned long	end;

	end = ft_set_time() + sleep_time;
	while (ft_set_time() < end)
		usleep(100);
}

int	ft_print(int i, int j, t_threads *threads)
{
	if (threads[0].win == -1 && j != 4)
		return (0);
	threads[i].status = j;
	threads[i].time = ft_set_time() - threads[0].initial_time;
	if (j == 0)
		return (printf("%d %d has taken a fork\n", threads[i].time, i + 1));
	if (j == 1)
		threads[i].last_eat = threads[i].time + threads[0].initial_time;
	if (j == 1)
		return (printf("%d %d is eating\n", threads[i].time, i + 1));
	if (j == 2)
		return (printf("%d %d is sleeping\n", threads[i].time, i + 1));
	if (j == 3)
		return (printf("%d %d is thinking\n", threads[i].time, i + 1));
	if (j == 4)
		return (printf("%d %d died\n", threads[i].time, i + 1));
	return (-1);
}

int	ft_theloop(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->mutex[philos->threads[i].left]);
	if (!(ft_print(i, 0, philos->threads)))
	{
		pthread_mutex_unlock(&philos->mutex[philos->threads[i].left]);
		return (0);
	}
	pthread_mutex_lock(&philos->mutex[i]);
	ft_print(i, 0, philos->threads);
	if (!(ft_print(i, 1, philos->threads)))
	{
		pthread_mutex_unlock(&philos->mutex[philos->threads[i].left]);
		pthread_mutex_unlock(&philos->mutex[i]);
		return (0);
	}
	ft_usleep(philos->time_to_eat);
	pthread_mutex_unlock(&philos->mutex[philos->threads[i].left]);
	pthread_mutex_unlock(&philos->mutex[i]);
	if (++philos->threads[i].done == philos->wincon)
		philos->threads[0].win++;
	if (!(ft_print(i, 2, philos->threads)))
		return (0);
	ft_usleep(philos->time_to_sleep);
	if (!(ft_print(i, 3, philos->threads)))
		return (0);
	return (1);
}

void	*ft_philoop(void *args)
{
	t_philo			*philos;
	int				i;

	philos = (t_philo *)args;
	i = philos->index;
	philos->threads[i].done = 0;
	philos->threads[i].last_eat = ft_set_time();
	ft_print(i, 3, philos->threads);
	if (philos->num_of_philo == 1)
	{
		ft_print(i, 0, philos->threads);
		ft_usleep(philos->time_to_die);
		return (0);
	}
	if (!i)
		philos->threads[i].left = philos->num_of_philo - 1;
	else
		philos->threads[i].left = i - 1;
	while (ft_theloop(philos, i))
		continue ;
	return (0);
}

void	*ft_checkloop(void *args)
{
	t_philo			*philos;
	int				i;

	philos = (t_philo *)args;
	pthread_mutex_lock(&philos->dead);
	while (philos->threads[0].win != philos->num_of_philo)
	{
		i = -1;
		while (++i < philos->num_of_philo)
		{
			philos->threads[i].time = ft_set_time()
				- philos->threads[i].last_eat;
			if (philos->threads[i].time >= philos->time_to_die)
				break ;
			usleep(20);
		}
		if (i != philos->num_of_philo && philos->threads[i++].time
			>= philos->time_to_die)
			break ;
	}
	philos->threads[0].win = -1;
	if (philos->threads[--i].time >= philos->time_to_die)
		ft_print(i, 4, philos->threads);
	pthread_mutex_unlock(&philos->dead);
	return (0);
}
