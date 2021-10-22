/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:16:17 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/22 15:59:47 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleepthink(t_threads *threads)
{
	if (++threads->done == threads->philo->wincon)
	{
		pthread_mutex_lock(&threads->philo->protect);
		threads->philo->win++;
		pthread_mutex_unlock(&threads->philo->protect);
	}
	pthread_mutex_lock(&threads->philo->write);
	if (!(ft_print(2, threads)))
	{
		pthread_mutex_unlock(&threads->philo->write);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->write);
	ft_usleep(threads->philo->time_to_sleep, threads);
	pthread_mutex_lock(&threads->philo->write);
	if (!(ft_print(3, threads)))
	{
		pthread_mutex_unlock(&threads->philo->write);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->write);
	return (1);
}

int	ft_theloop(t_threads *threads)
{
	pthread_mutex_lock(&threads->philo->mutex[threads->left]);
	pthread_mutex_lock(&threads->philo->write);
	if (!(ft_print(0, threads)))
	{
		pthread_mutex_unlock(&threads->philo->mutex[threads->left]);
		pthread_mutex_unlock(&threads->philo->write);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->write);
	pthread_mutex_lock(&threads->philo->mutex[threads->index]);
	pthread_mutex_lock(&threads->philo->write);
	if (!ft_print(0, threads) || !(ft_print(1, threads)))
	{
		pthread_mutex_unlock(&threads->philo->mutex[threads->left]);
		pthread_mutex_unlock(&threads->philo->mutex[threads->index]);
		pthread_mutex_unlock(&threads->philo->write);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->write);
	ft_usleep(threads->philo->time_to_eat, threads);
	pthread_mutex_unlock(&threads->philo->mutex[threads->left]);
	pthread_mutex_unlock(&threads->philo->mutex[threads->index]);
	if (!ft_sleepthink(threads))
		return (0);
	return (1);
}

void	*ft_philoop(void *args)
{
	t_threads			*threads;

	threads = (t_threads *)args;
	threads->done = 0;
	pthread_mutex_lock(&threads->philo->write);
	ft_print(3, threads);
	if (threads->philo->num_of_philo == 1)
	{
		ft_print(0, threads);
		ft_usleep(threads->philo->time_to_die, threads);
		pthread_mutex_unlock(&threads->philo->write);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->write);
	if (!threads->index)
		threads->left = threads->philo->num_of_philo - 1;
	else
		threads->left = threads->index - 1;
	while (ft_theloop(threads))
		continue ;
	return (0);
}

int	ft_check(t_philo *philo, int *i)
{
	pthread_mutex_unlock(&philo->protect);
	while (++(*i) < philo->num_of_philo)
	{
		pthread_mutex_lock(&philo->write);
		philo->limit[*i] = ft_set_time() - philo->last[*i];
		pthread_mutex_unlock(&philo->write);
		if (philo->limit[*i] >= philo->time_to_die)
		{
			pthread_mutex_lock(&philo->protect);
			return (1);
		}
	}
	pthread_mutex_lock(&philo->protect);
	return (0);
}

void	*ft_checkloop(void *args)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->protect);
	while (philo->win != philo->num_of_philo)
	{
		i = -1;
		if (ft_check(philo, &i))
			break ;
	}
	if (philo->win == philo->num_of_philo)
		i--;
	pthread_mutex_unlock(&philo->protect);
	pthread_mutex_lock(&philo->exit);
	philo->end = -1;
	pthread_mutex_unlock(&philo->exit);
	pthread_mutex_lock(&philo->write);
	if (philo->limit[i] >= philo->time_to_die)
		printf("%d %d died\n", (int)ft_set_time() - philo->init, i + 1);
	pthread_mutex_unlock(&philo->write);
	return (0);
}
