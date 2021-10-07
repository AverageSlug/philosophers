/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:17 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/07 18:37:19 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(int i, int j, t_threads *threads)
{
	struct timeval	todms;

	gettimeofday(&todms, NULL);
	threads[i].time = todms.tv_sec * 1000 + todms.tv_usec / 1000 - threads[0].initial_time;
	if (threads[0].win == -1 && j != 4)
		return (-1);
	threads[i].status = j;
	if (j == 0)
		return (printf("%d %d has taken a fork\n", threads[i].time, i + 1));
	if (j == 1)
		threads[i].time_last_eat = threads[i].time;
	if (j == 1)
		return (printf("%d %d is eating\n", threads[i].time, i + 1));
	if (j == 2)
		return (printf("%d %d is sleeping\n", threads[i].time, i + 1));
	if (j == 3)
		return (printf("%d %d is thinking\n", threads[i].time, i + 1));
	if (j == 4)
		return (printf("%d %d died\n", threads[i].time, i + 1));
	return (0);
}

void	*ft_philoop(void *args)
{
	t_philo			*philos;
	int				i;
	int				j;

	philos = (t_philo *)args;
	i = philos->index;
	j = 0;
	if (!i)
		philos->threads[i].left = philos->num_of_philo - 1;
	else
		philos->threads[i].left = i - 1;
	ft_print(i, 19, philos->threads);
	philos->threads[i].time_last_eat = philos->threads[i].time;
	while (1)
	{
		pthread_mutex_lock(&philos->mutex[philos->threads[i].left]);
		if (!(ft_print(i, 0, philos->threads)))
			return (0);
		pthread_mutex_lock(&philos->mutex[i]);
		if (!(ft_print(i, 0, philos->threads)))
			return (0);
		if (!(ft_print(i, 1, philos->threads)))
			return (0);
		usleep(philos->time_to_eat * 1000);
		if (++j == philos->wincon)
			philos->threads[0].win++;
		if (!(ft_print(i, 2, philos->threads)))
			return (0);
		pthread_mutex_unlock(&philos->mutex[philos->threads[i].left]);
		pthread_mutex_unlock(&philos->mutex[i]);
		usleep(philos->time_to_sleep * 1000);
		if (!(ft_print(i, 3, philos->threads)))
			return (0);
	}
	return (0);
}

void	ft_unlock(t_philo *philos)
{
	int	j;

	j = -1;
	while (++j < philos->num_of_philo)
	{
		if (philos->threads[j].status == 0)
		{
			pthread_mutex_unlock(&philos->mutex[philos->threads[j].left]);
			pthread_mutex_destroy(&philos->mutex[philos->threads[j].left]);
		}
		if (philos->threads[j].status == 1)
		{
			pthread_mutex_unlock(&philos->mutex[philos->threads[j].left]);
			pthread_mutex_unlock(&philos->mutex[j]);
			pthread_mutex_destroy(&philos->mutex[philos->threads[j].left]);
			pthread_mutex_destroy(&philos->mutex[j]);
		}
	}
}

void	*ft_checkloop(void *args)
{
	t_philo			*philos;
	int				i;

	philos = (t_philo *)args;
	pthread_mutex_lock(&philos->dead);
	while (1)
	{
		i = -1;
		while (++i < philos->num_of_philo)
		{
			if (philos->threads[i].time - philos->threads->time_last_eat > philos->time_to_die)
			{
				philos->threads[0].win = -1;
				ft_unlock(philos);
				ft_print(i, 4, philos->threads);
				pthread_mutex_unlock(&philos->dead);
				return (0);
			}
			usleep(20);
		}
		if (philos->threads[0].win == philos->num_of_philo)
		{
			philos->threads[0].win = -1;
			ft_unlock(philos);
			pthread_mutex_unlock(&philos->dead);
			return (0);
		}
	}
	return (0);
}
