/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:15:42 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/19 13:58:31 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned long sleep_time, t_threads *threads)
{
	unsigned long	end;

	end = ft_set_time() + sleep_time;
	while (ft_set_time() < end && !threads->philo->end)
		usleep(100);
}

int	ft_print(int j, t_threads *threads)
{
	pthread_mutex_lock(&threads->philo->protect);
	if (threads->philo->end == -1 && j != 4)
	{
		pthread_mutex_unlock(&threads->philo->protect);
		return (0);
	}
	pthread_mutex_unlock(&threads->philo->protect);
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
