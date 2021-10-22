/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:15:42 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/22 15:47:47 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned long sleep_time, t_threads *threads)
{
	unsigned long	end;

	end = ft_set_time() + sleep_time;
	pthread_mutex_lock(&threads->philo->exit);
	while (ft_set_time() < end && !threads->philo->end)
	{
		pthread_mutex_unlock(&threads->philo->exit);
		usleep(200);
		pthread_mutex_lock(&threads->philo->exit);
	}
	pthread_mutex_unlock(&threads->philo->exit);
}

int	ft_print(int j, t_threads *threads)
{
	pthread_mutex_lock(&threads->philo->exit);
	if (threads->philo->end == -1)
	{
		pthread_mutex_unlock(&threads->philo->exit);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->exit);
	threads->time = ft_set_time() - threads->philo->init;
	if (j == 0)
		printf("%d %d has taken a fork\n", threads->time, threads->index + 1);
	if (j == 1)
		threads->philo->last[threads->index] = threads->time
			+ threads->philo->init;
	if (j == 1)
		printf("%d %d is eating\n", threads->time, threads->index + 1);
	if (j == 2)
		printf("%d %d is sleeping\n", threads->time, threads->index + 1);
	if (j == 3)
		printf("%d %d is thinking\n", threads->time, threads->index + 1);
	return (1);
}
