/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:17 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:05:55 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_threads	*g_threads;

void	ft_unlock(t_philo *philos, int i)
{
	pthread_mutex_unlock(&philos->mutex[g_threads[i].left]);
	pthread_mutex_unlock(&philos->mutex[i]);
}

void	ft_time_set(int i, int j)
{
	struct timeval	todms;

	gettimeofday(&todms, NULL);
	g_threads[i].time = todms.tv_sec * 1000 + todms.tv_usec / 1000;
	g_threads[i].status = j;
	if (j == 0)
		printf("%d %d has taken a fork\n", g_threads[i].time, i + 1);
	if (j == 1)
		printf("%d %d is eating\n", g_threads[i].time, i + 1);
	if (j == 1)
		g_threads[i].time_last_eat = g_threads[i].time;
	if (j == 2)
		printf("%d %d is sleeping\n", g_threads[i].time, i + 1);
	if (j == 3)
		printf("%d %d is thinking\n", g_threads[i].time, i + 1);
	if (j == 4)
		printf("%d %d died\n", g_threads[i].time, i + 1);
}

void	*ft_philoop(void *args)
{
	t_philo			*philos;
	int				i;
	int				j;

	philos = (t_philo *)args;
	i = philos->index;
	j = 0;
	if (philos->num_of_philo == 1)
	{
		ft_time_set(i, 0);
		usleep(philos->time_to_die * 1000);
		ft_time_set(i, 4);
		return (0);
	}
	if (!i)
		g_threads[i].left = philos->num_of_philo - 1;
	else
		g_threads[i].left = i - 1;
	if (i == philos->num_of_philo - 1)
		g_threads[i].right = 0;
	else
		g_threads[i].right = i + 1;
	ft_time_set(i, -1);
	g_threads[i].time_last_eat = g_threads->time;
	while (1)
	{
		if (g_threads[g_threads[i].left].status == 1 && g_threads[g_threads[i].left].time_last_eat - g_threads[i].time_last_eat - philos->time_to_eat > philos->time_to_die)
		{
			usleep(philos->time_to_die - g_threads[i].time + g_threads[i].time_last_eat);
			ft_time_set(i, 4);
			return (0);
		}
		pthread_mutex_lock(&philos->mutex[g_threads[i].left]);
		ft_time_set(i, 0);
		if (g_threads[g_threads[i].right].status == 1 && g_threads[g_threads[i].right].time_last_eat - g_threads[i].time_last_eat - philos->time_to_eat > philos->time_to_die)
		{
			usleep(philos->time_to_die - g_threads[i].time + g_threads[i].time_last_eat);
			ft_time_set(i, 4);
			return (0);
		}
		pthread_mutex_lock(&philos->mutex[i]);
		ft_time_set(i, 0);
		ft_time_set(i, 1);
		if (philos->time_to_eat > philos->time_to_die)
		{
			usleep(philos->time_to_die * 1000);
			ft_unlock(philos, i);
			ft_time_set(i, 4);
			return (0);
		}
		usleep(philos->time_to_eat * 1000);
		if (++j == philos->wincon)
			ft_unlock(philos, i);
		if (j == philos->wincon)
			return (0);
		ft_time_set(i, 2);
		ft_unlock(philos, i);
		if (philos->time_to_eat + philos->time_to_sleep > philos->time_to_die)
		{
			usleep((philos->time_to_die - philos->time_to_eat) * 1000);
			ft_time_set(i, 4);
			return (0);
		}
		usleep(philos->time_to_sleep * 1000);
		ft_time_set(i, 3);
	}
	return (0);
}

int	ft_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philo)
	{
		philo->index = i;
		if (pthread_create(&philo->pthread[i], NULL, ft_philoop, (void *)philo))
			return (0);
		usleep(10);
	}
	i = -1;
	while (++i < philo->num_of_philo)
	{
		pthread_join(philo->pthread[i], NULL);
		if (g_threads[i].status == 4)
			return (1);
	}
	return (1);
}

int	ft_pthread(t_philo *philo)
{
	int	i;

	philo->pthread = malloc(sizeof(pthread_t) * philo->num_of_philo);
	if (!philo->pthread)
		return (0);
	philo->mutex = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (!philo->mutex)
		return (ft_clearall(0, philo));
	g_threads = malloc(sizeof(g_threads) * philo->num_of_philo);
	if (!g_threads)
		return (ft_clearall(0, philo));
	i = 0;
	while (i < philo->num_of_philo)
	{
		g_threads[i].status = 5;
		pthread_mutex_init(&philo->mutex[i++], NULL);
	}
	if (!(ft_philos(philo)))
		return (ft_clearall(0, philo));
	return (ft_clearall(1, philo));
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (1);
	if (!(ft_parse(argc, argv, &philo)))
		return (1);
	if (!(ft_pthread(&philo)))
		return (1);
	return (0);
}